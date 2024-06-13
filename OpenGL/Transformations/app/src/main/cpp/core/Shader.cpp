//
// Created by lixianru on 2024/5/14.
//

#include "Shader.h"
#include <utils/Log.h>
#include "GLEnv.h"
#include <string>

Shader::Shader():mProgram(0) {}

Shader::~Shader() {
    if(!mProgram){
        glDeleteProgram(mProgram);
    }
}

void Shader::setSource(const char *vsSource,const char * fsSource){//make current
    GLuint vs, fs;
    vs = compileShader(GL_VERTEX_SHADER, vsSource);
    if(vs == 0){
        return;
    }
    fs = compileShader(GL_FRAGMENT_SHADER, fsSource);
    if(fs == 0){
        glDeleteShader(vs);
        return;
    }
    GLuint shaders[] = {vs,fs};
    mProgram = linkProgram(shaders, 2);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

bool Shader::useProgram() {
    if(!mProgram) return false;
    glUseProgram(mProgram);
    return true;
}

bool Shader::unuseProgram() {
    glUseProgram(0);
    return true;
}
//wait egl ready
GLuint Shader::compileShader(GLenum shader_type, const char* source) {
    //LOGE("Shader::compileShader shader_type %d source %s",shader_type,source);
    // Create shader
    GLuint shader = glCreateShader(shader_type);
    if (GLEnv::CheckGLError("glCreateShader")) return 0;
    if(!shader){
        LOGE("compileShader glCreateShader failed");
        return shader;
    }
    //attach source to shader object
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled){
        std::string src(source);
        size_t cur_pos = 0;
        size_t next_pos = 0;
        size_t line_number = 1;
        while ( (next_pos = src.find_first_of('\n', cur_pos)) != std::string::npos) {
            LOGE("%03zd : %s", line_number, src.substr(cur_pos, next_pos-cur_pos).c_str());
            cur_pos = next_pos + 1;
            line_number++;
        }
        LOGE("%03zu : %s", line_number, src.substr(cur_pos, next_pos-cur_pos).c_str());

        GLint log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        if (log_length) {
            char* error_log = new char[log_length];
            if (error_log) {
                glGetShaderInfoLog(shader, log_length, NULL, error_log);
                LOGE("Shader compilation error %d:\n%s\n", shader_type, error_log);
                delete[] error_log;
            }
        }
        glDeleteShader(shader);
        shader = 0;
    }
    return shader;
}

GLuint Shader::linkProgram(GLuint *shaders, GLuint count) {
    LOGI("Shader::linkProgram count %d", count);
    GLuint program = glCreateProgram();
    if (GLEnv::CheckGLError("glCreateProgram")) return 0;
    if (program) {
        // Attach all compiled shaders
        for (GLuint i = 0; i < count; ++i) {
            glAttachShader(program, shaders[i]);
            if (GLEnv::CheckGLError("glAttachShader")) return 0;
        }

        // Link
        glLinkProgram(program);

        // Check for linking errors
        GLint linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (linked != GL_TRUE) {
            // Log the linker error messages
            GLint log_length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
            if (log_length) {
                char* error_log = new char[log_length];
                if (error_log) {
                    glGetProgramInfoLog(program, log_length, NULL, error_log);
                    LOGE("Program Linker Error:\n%s\n", error_log);
                    delete[] error_log;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint Shader::getUniformLocation(std::string name) {
    GLuint location;
    if(mLocations.find(name) == mLocations.end()){
        location = glGetUniformLocation(mProgram, name.c_str());
        mLocations[name] = location;
    }else{
        location = mLocations[name];
    }
    return location;
}
GLuint Shader::getAttribLocation(std::string name){
    return glGetAttribLocation(mProgram, name.c_str());
}

void Shader::setInt(std::string name, int value) {
    GLuint location = getUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::setMatrix4f(std::string name, glm::mat4 &value) {
    GLuint location = getUniformLocation(name);
    glUniformMatrix4fv(location,1, GL_FALSE, glm::value_ptr(value));
}

