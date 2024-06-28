//
// Created by lixianru on 2024/5/14.
//

#include "Application.h"
#include "Asset.h"
#include "utils/Log.h"
#include <object/Object.h>



Application::Application(ANativeActivity *activity) {
    Object::activity = activity;
    mObject = Object::createObject("camera");


}

Application::~Application() {
    if(mObject != nullptr) {
        delete mObject;
        mObject = nullptr;
    }
}

void Application::initWindow(ANativeWindow *nativeWindow) {
    mEglManager.createSwapChain(nativeWindow);
    if(!mEglManager.makeCurrent()){
        LOGE("MakeCurrent failed");
        return;
    }

    int32_t w = ANativeWindow_getWidth(nativeWindow);
    int32_t h = ANativeWindow_getHeight(nativeWindow);
    if(mObject != nullptr){
        mObject->init(w,h);
    }
    mCamera  = new PerspectiveCamera(45,(float)w / (float)h,0.1,1000);

}

void Application::termWindow() {
    mEglManager.onWindowDestory();
}

bool Application::beginFrame() {
    return mEglManager.makeCurrent();
}

void Application::endFrame() {
    mEglManager.swapBuffer();
}

void Application::process() {
    if(mObject == nullptr || mCamera == nullptr) return;


    if(beginFrame()){
        mObject->onDraw(mCamera);
        endFrame();
    }
}