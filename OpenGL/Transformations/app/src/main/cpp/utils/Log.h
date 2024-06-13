//
// Created by lixianru on 2024/5/14.
//

#ifndef OPENGLTRIANGLE_LOG_H
#define OPENGLTRIANGLE_LOG_H

#include <android/log.h>

#define LOG_TAG "OpenGLTriangle"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //OPENGLTRIANGLE_LOG_H
