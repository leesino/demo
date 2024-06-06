//
// Created by lixianru on 2024/5/15.
//

#include "GLEnv.h"
#include <utils/Log.h>


bool GLEnv::CheckGLError(const std::string& op) {
    bool err = false;
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGE("GL Error: Operation '%s' caused GL error (0x%x)\n",
              op.c_str(),
              error);
        err = true;
        throw "error occur";
    }
    return err;
}