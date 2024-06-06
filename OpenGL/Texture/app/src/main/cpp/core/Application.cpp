//
// Created by lixianru on 2024/5/14.
//

#include "Application.h"
#include "Asset.h"
#include "utils/Log.h"
#include <object/Object.h>

Application::Application(ANativeActivity *activity) {
    Object::activity = activity;
    mObject = Object::createObject("texture");
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
    if(mObject != nullptr){
        mObject->init();
    }
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
    if(mObject == nullptr) return;
    if(beginFrame()){
        mObject->onDraw();
        endFrame();
    }
}