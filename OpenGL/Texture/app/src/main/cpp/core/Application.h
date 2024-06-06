//
// Created by lixianru on 2024/5/14.
//

#ifndef OPENGLTRIANGLE_APPLICATION_H
#define OPENGLTRIANGLE_APPLICATION_H

#include <object/Object.h>
#include "Shader.h"
#include "EglManager.h"
#include <android/native_activity.h>
#include <memory>

class Application {
public:
    Application(ANativeActivity *activity);
    ~Application();
    void initWindow(ANativeWindow *nativeWindow);
    void termWindow();
    bool beginFrame();
    void endFrame();
    void process();
private:
    Object * mObject;
    EglManager mEglManager;
};


#endif //OPENGLTRIANGLE_APPLICATION_H
