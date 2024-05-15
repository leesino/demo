
#include <android_native_app_glue.h>
#include <jni.h>
#include <exception>
#include <android/log.h>

#define LOG_TAG "Native"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

struct AndroidAppState {
    ANativeWindow* NativeWindow = nullptr;
    bool Resumed = false;
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
            appState->NativeWindow = NULL;
            break;
        }
        case APP_CMD_INIT_WINDOW: {
            appState->NativeWindow = app->window;

            break;
        }
        case APP_CMD_TERM_WINDOW: {
            appState->NativeWindow = NULL;
            break;
        }
    }
}



static int32_t handleInputEvent(struct android_app* app, AInputEvent* event)
{
    LOGI("android_main handleInputEvent");
    if(AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION 
     && AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN){
        int32_t action = AMotionEvent_getAction(event);
        float x = AMotionEvent_getX(event,0);
        float y = AMotionEvent_getY(event,0);
        switch(action){
        case AMOTION_EVENT_ACTION_DOWN:
            LOGI("android_main AMOTION_EVENT_ACTION_DOWN (x %f, y %f)", x,y);
            break;
        case AMOTION_EVENT_ACTION_MOVE:
            LOGI("android_main AMOTION_EVENT_ACTION_MOVE");
            break;
        case AMOTION_EVENT_ACTION_UP:
            LOGI("android_main AMOTION_EVENT_ACTION_UP");
            break;
        default:
            break;
        }
    
    }

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

        AndroidAppState appState = {};

        app->userData = &appState;
        app->onAppCmd = handleAppCmd;
        app->onInputEvent = handleInputEvent;


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
            
            if(appState.NativeWindow != nullptr){
                ANativeWindow_setBuffersGeometry(appState.NativeWindow, 100, 100, WINDOW_FORMAT_RGBA_8888);
                ANativeWindow_Buffer buffer;
                if (ANativeWindow_lock(appState.NativeWindow, &buffer, nullptr) == 0) {
                    uint32_t* bits = static_cast<uint32_t*>(buffer.bits);
                    for (int i = 0; i < buffer.stride * buffer.height; i++) {
                        bits[i] = 0xFFFFFFFF;//ABGR 
                    }

                    ANativeWindow_unlockAndPost(appState.NativeWindow);
                }
            }
            LOGI("android_main loop");//why is 16
            
            //handle

        }
        app->activity->vm->DetachCurrentThread();
    } catch (const std::exception& ex) {
        LOGE("%s",ex.what());
    } catch (...) {
        LOGE("Unknow Error");
    }
}
