//
// Created by lixianru on 2024/5/14.
//

#ifndef OPENGLTRIANGLE_EGLMANAGER_H
#define OPENGLTRIANGLE_EGLMANAGER_H
#include <EGL/egl.h>
#include <EGL/eglext.h>

class EglManager {
public:
    EglManager();
    ~EglManager();
    void destroy();
    void createSwapChain(ANativeWindow *nativeWindow);
    void onWindowDestory();
    bool makeCurrent();
    void swapBuffer();

private:
    EGLDisplay mEglDisplay;
    EGLConfig  mEglConfig;
    EGLContext mEglContext;
    EGLSurface mEglSurface;

    EGLConfig config;
    EGLint numConfigs;
    EGLint format;
    bool mIsInited;
};


#endif //OPENGLTRIANGLE_EGLMANAGER_H
