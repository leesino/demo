//
// Created by lixianru on 2024/5/14.
//

#ifndef OPENGLTRIANGLE_SHADER_H
#define OPENGLTRIANGLE_SHADER_H
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>

class Shader {
public:
    Shader();
    ~Shader();
    void setSource(const char *vsSource,const char * fsSource);
    bool useProgram();
    bool unuseProgram();

private:
    GLuint compileShader(GLenum shader_type, const char* source);
    GLuint linkProgram(GLuint* shaders, GLuint count);

    GLuint mProgram;
};


#endif //OPENGLTRIANGLE_SHADER_H