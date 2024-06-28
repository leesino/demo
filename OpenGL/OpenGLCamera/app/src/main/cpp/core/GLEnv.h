//
// Created by lixianru on 2024/5/15.
//

#ifndef OPENGLTRIANGLE_GLENV_H
#define OPENGLTRIANGLE_GLENV_H
#include <string>

#include <GLES3/gl3.h>
#include <EGL/egl.h>

class GLEnv {
public:
    static bool CheckGLError(const std::string& operation);

};


#endif //OPENGLTRIANGLE_GLENV_H
