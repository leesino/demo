//
// Created by lixianru on 2024/5/14.
//

#ifndef OPENGLTRIANGLE_SHADER_H
#define OPENGLTRIANGLE_SHADER_H
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include <string>
#include <map>
#include <core/pch.h>
class Shader {
public:
    Shader();
    ~Shader();
    void setSource(const char *vsSource,const char * fsSource);
    bool useProgram();
    bool unuseProgram();

    void setInt(std::string name, int value);
    void setMatrix4f(std::string name, glm::mat4 &value);

    GLuint getUniformLocation(std::string name);
    GLuint getAttribLocation(std::string name);

private:
    GLuint compileShader(GLenum shader_type, const char* source);
    GLuint linkProgram(GLuint* shaders, GLuint count);

    std::map<std::string, GLuint> mLocations;

    GLuint mProgram;
};


#endif //OPENGLTRIANGLE_SHADER_H