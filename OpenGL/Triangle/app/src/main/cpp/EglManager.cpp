//
// Created by lixianru on 2024/5/14.
//

#include <android/native_window.h>
#include <GLES2/gl2.h>
#include "EglManager.h"
#include "Log.h"

#define ERROR_CASE(x) \
    case x:           \
        return #x;
static const char* egl_error_str(EGLint error) {
    switch (error) {
        ERROR_CASE(EGL_SUCCESS)
        ERROR_CASE(EGL_NOT_INITIALIZED)
        ERROR_CASE(EGL_BAD_ACCESS)
        ERROR_CASE(EGL_BAD_ALLOC)
        ERROR_CASE(EGL_BAD_ATTRIBUTE)
        ERROR_CASE(EGL_BAD_CONFIG)
        ERROR_CASE(EGL_BAD_CONTEXT)
        ERROR_CASE(EGL_BAD_CURRENT_SURFACE)
        ERROR_CASE(EGL_BAD_DISPLAY)
        ERROR_CASE(EGL_BAD_MATCH)
        ERROR_CASE(EGL_BAD_NATIVE_PIXMAP)
        ERROR_CASE(EGL_BAD_NATIVE_WINDOW)
        ERROR_CASE(EGL_BAD_PARAMETER)
        ERROR_CASE(EGL_BAD_SURFACE)
        ERROR_CASE(EGL_CONTEXT_LOST)
        default:
            return "Unknown error";
    }
}
const char* eglErrorString() {
    return egl_error_str(eglGetError());
}

EglManager::EglManager()
        : mEglDisplay(EGL_NO_DISPLAY)
        , mEglConfig(nullptr)
        , mEglContext(EGL_NO_CONTEXT)
        , mEglSurface(EGL_NO_SURFACE)
        , mIsInited(false){

}

EglManager::~EglManager(){
    destroy();
}

void EglManager::destroy() {
    if (mEglDisplay == EGL_NO_DISPLAY) return;

    eglDestroyContext(mEglDisplay, mEglContext);
    if (mEglSurface != EGL_NO_SURFACE) {
        eglDestroySurface(mEglDisplay, mEglSurface);
    }
    eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglTerminate(mEglDisplay);
    eglReleaseThread();

    mEglDisplay = EGL_NO_DISPLAY;
    mEglContext = EGL_NO_CONTEXT;
    mEglSurface = EGL_NO_SURFACE;
}

void EglManager::initialize(ANativeWindow *nativeWindow) {

    mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(mEglDisplay == EGL_NO_DISPLAY){
        return;
    }
    EGLint major, minor;
    if(eglInitialize(mEglDisplay, &major, &minor) == EGL_FALSE){
        LOGI( "Failed to initialize display %p! err=%s", mEglDisplay, eglErrorString());
        return;
    }

    const EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
            EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
    };

    if (!eglChooseConfig(mEglDisplay, attribs, &config, 1, &numConfigs)) {
        LOGE("eglChooseConfig() returned error %d", eglGetError());
        destroy();
        return;
    }

    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };
    if (!(mEglContext = eglCreateContext(mEglDisplay, config, 0, ctxAttr))) {
        LOGE("eglCreateContext() returned error %d", eglGetError());
        destroy();
        return;
    }

    ANativeWindow_setBuffersGeometry(nativeWindow, 0, 0, format);

    if (!(mEglSurface = eglCreateWindowSurface(mEglDisplay, config, nativeWindow, 0))) {
        LOGE("eglCreateWindowSurface() returned error %d", eglGetError());
        destroy();
        return;
    }

    if (!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
        LOGE("eglMakeCurrent() returned error %d", eglGetError());
        destroy();
        return;
    }

    EGLint width;
    EGLint height;
    if (!eglQuerySurface(mEglDisplay, mEglSurface, EGL_WIDTH, &width) ||
        !eglQuerySurface(mEglDisplay, mEglSurface, EGL_HEIGHT, &height)) {
        LOGE("eglQuerySurface() returned error %d", eglGetError());
        destroy();
        return;
    }

    glViewport(0, 0, width, height);

    mIsInited = true;
}

bool EglManager::makeCurrent() {
    if(!mIsInited) return false;
    if (!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
        LOGE("eglMakeCurrent() returned error %d", eglGetError());
        return false;
    }

    return true;
}

void EglManager::swapBuffer() {
    if(!mIsInited) return;
    if (!eglSwapBuffers(mEglDisplay, mEglSurface)) {
        LOGE("eglSwapBuffers() returned error %d", eglGetError());
    }
}