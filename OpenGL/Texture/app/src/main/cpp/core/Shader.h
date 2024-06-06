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

class Shader {
public:
    Shader();
    ~Shader();
    void setSource(const char *vsSource,const char * fsSource);
    bool useProgram();
    bool unuseProgram();

    void setInt(std::string name, int value);

private:
    GLuint compileShader(GLenum shader_type, const char* source);
    GLuint linkProgram(GLuint* shaders, GLuint count);

    std::map<std::string, GLuint> mLocations;
    GLuint getLocation(std::string name);
    GLuint mProgram;
};


#endif //OPENGLTRIANGLE_SHADER_H