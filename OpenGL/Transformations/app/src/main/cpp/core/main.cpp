
#include <android_native_app_glue.h>
#include <jni.h>
#include <exception>
#include "Application.h"
#include <utils/Log.h>


struct AndroidAppState {
    bool Resumed = false;
    ANativeWindow *window = nullptr;
    Application *application = nullptr;
};

static void handleAppCmd(struct android_app* app, int32_t cmd) {
    AndroidAppState* appState = (AndroidAppState*)app->userData;

    switch (cmd) {
        case APP_CMD_START: {
            break;
        }
        case APP_CMD_RESUME: {
            appState->Resumed = true;
            break;
        }
        case APP_CMD_PAUSE: {
            appState->Resumed = false;
            break;
        }
        case APP_CMD_STOP: {
            break;
        }
        case APP_CMD_DESTROY: {
            break;
        }
        case APP_CMD_INIT_WINDOW: {
            appState->application->initWindow(app->window);
            break;
        }
        case APP_CMD_TERM_WINDOW: {
            appState->application->termWindow();
            break;
        }
    }
}

static int32_t handleInputEvent(struct android_app* app, AInputEvent* event)
{
    return 0;
}

void android_main(struct android_app* app)
{
    LOGI("android_main");
    try {
        JNIEnv* Env;
        app->activity->vm->AttachCurrentThread(&Env, nullptr);

        JavaVM *vm;
        Env->GetJavaVM(&vm);
        Application application = Application(app->activity);

        AndroidAppState appState = {};
        appState.application = &application;

        app->userData = &appState;
        app->onAppCmd = handleAppCmd;
        app->onInputEvent = handleInputEvent;
        bool initWindow = false;

        while (app->destroyRequested == 0) {
            for (;;) {
                int events;
                struct android_poll_source *source;
                const int timeoutMilliseconds =
                        (!appState.Resumed &&
                         app->destroyRequested == 0) ? -1 : 0;
                if (ALooper_pollAll(timeoutMilliseconds, nullptr, &events, (void **) &source) < 0) {
                    break;
                }
                if (source != nullptr) {
                    source->process(app, source);
                }
            }
            application.process();
        }
        app->activity->vm->DetachCurrentThread();
    } catch (const std::exception& ex) {
        LOGE("%s",ex.what());
    } catch (...) {
        LOGE("Unknow Error");
    }
}
