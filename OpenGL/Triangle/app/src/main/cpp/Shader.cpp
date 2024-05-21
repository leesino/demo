//
// Created by lixianru on 2024/5/14.
//

#include "Shader.h"
#include "Log.h"
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
    glUseProgram(mProgram);//todo check result
    return true;
}

bool Shader::unuseProgram() {
    glUseProgram(0);//todo check result
    return true;
}
//wait egl ready
GLuint Shader::compileShader(GLenum shader_type, const char* source) {
    //LOGE("Shader::compileShader shader_type %d source %s",shader_type,source);
    // Create shader
    GLuint shader = glCreateShader(shader_type);
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
    GLuint program = glCreateProgram();
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
