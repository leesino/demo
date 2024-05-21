//
// Created by lixianru on 2024/5/14.
//

#ifndef OPENGLTRIANGLE_TRIANGLE_H
#define OPENGLTRIANGLE_TRIANGLE_H

#include <memory>
#include <android/native_activity.h>
#include "Shader.h"

class Triangle {
public:
    Triangle(ANativeActivity *activity);
    ~Triangle();
    void init();
    void onDraw();

private:
    std::shared_ptr<Shader> mShader;
    ANativeActivity * mActivity;
    unsigned int VBO, VAO;
};


#endif //OPENGLTRIANGLE_TRIANGLE_H
