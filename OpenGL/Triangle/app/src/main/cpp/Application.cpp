//
// Created by lixianru on 2024/5/14.
//

#include "Application.h"
#include "Asset.h"


Application::Application(ANativeActivity *activity): mTriangle(activity) {
}

Application::~Application() {
}

void Application::createSwapChain(ANativeWindow *nativeWindow){
    mEglManager.initialize(nativeWindow);
    mTriangle.init();
}

bool Application::beginFrame() {
    return mEglManager.makeCurrent();
}

void Application::endFrame() {
    mEglManager.swapBuffer();
}

void Application::process() {
    if(beginFrame()){
        mTriangle.onDraw();
        endFrame();
    }
}