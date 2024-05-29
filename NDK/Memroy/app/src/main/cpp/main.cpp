
#include <android_native_app_glue.h>
#include <jni.h>
#include <exception>
#include <android/log.h>
#include <string.h>

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
    return 0;
}

typedef struct Node{
    void *ptr;
    size_t size;
    char *file;
    size_t line;
    struct Node *next;
} Node;


Node *head = nullptr;
void addRecord(void *ptr, size_t size, const char *file, size_t line){
    LOGI("addRecord");
    Node * node = (Node *)malloc(sizeof(Node));
    node->ptr = ptr;
    node->size = size;
    node->file = (char *)malloc(strlen(file)+1);
    strcpy(node->file,file);
    node->line = line;
    node->next= nullptr;
    if(head == nullptr){
        head = node;
    } else{
        node->next = head;
        head = node;
    }
}
void removeRecord(void *ptr){
    if(head == nullptr) return;
    Node *p = head;
    if(p->ptr == ptr){
        head = head->next;
        if(p->file != nullptr){
            free(p->file);
        }
        free(p);
        return;
    }
    Node * q = p->next;
    while (q != nullptr){
        if(q->ptr == ptr){
            p->next = q->next;
            if(q->file != nullptr){
                free(q->file);
            }
            free(q);
            return;
        }
        p = q;
        q = q->next;
    }
}

int showSnapshot(){
    LOGI("========Memory Snapshot Begin=========");
    int total = 0;
    Node *p = head;
    while (p != nullptr){
        total += p->size;
        LOGI("file %s line %d allocate size %d", p->file,p->line, p->size);
        p = p->next;
    }
    LOGI("total memory allocate is %d", total);
    LOGI("========Memory Snapshot End=========");
    return total;
}

void * operator new(size_t size,const char * file, size_t line){
    LOGI("new size %d file: %s line %d",size, file, line);
    void *ptr = malloc(size);
    if(ptr != nullptr){
        addRecord(ptr, size, file, line);
    }
    return ptr;
}

void * operator new[](size_t size,const char * file, size_t line){
    LOGI("new array size %d file: %s line %d",size, file, line);
    void *ptr = malloc(size);
    if(ptr != nullptr){
        addRecord(ptr, size, file, line);
    }
    return ptr;
}

void operator delete(void *ptr) {
    if(ptr == nullptr) return;
    removeRecord(ptr);
    free(ptr);
}
void operator delete[](void *ptr) {
    if(ptr == nullptr) return;
    removeRecord(ptr);
    free(ptr);
}

#define new new(__FILE__,__LINE__)



class MEM{
public:
    MEM(){
        LOGI("MEM constructor");
    }
    ~MEM(){
        LOGI("MEM destructor");
    }
private:
    int a;
};

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

        {
            showSnapshot();
            int *p1 = new int(3);
            int *p2 = new int[5];
            MEM * p3 = new MEM();
            MEM * p4 = new MEM[5];
            showSnapshot();
            delete p1;
            delete []p2;
            delete p3;
            delete []p4;
            showSnapshot();

        }


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
           // LOGI("android_main loop");//why is 16
            
            //handle

        }
        app->activity->vm->DetachCurrentThread();
    } catch (const std::exception& ex) {
        LOGE("%s",ex.what());
    } catch (...) {
        LOGE("Unknow Error");
    }
}
