//
// Created by lixianru on 2024/5/17.
//

#include "TextureSample.h"
#include "core/GLEnv.h"
#include <core/Asset.h>
#include <core/Texture.h>

TextureSample::TextureSample() {
    VAO = VBO = EBO = 0;
}

TextureSample::~TextureSample() {
    if(VAO != 0){
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if(VBO != 0){
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if(EBO != 0){
        glDeleteBuffers(1,&EBO);
    }
}

void TextureSample::init() {
    float vertices[] = {
        //     ---- 位置 ----         - 纹理坐标 -
            0.5f,  0.5f, 0.0f,      1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f,      1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,     0.0f, 1.0f    // 左上
    };

    glGenBuffers(1, &VBO);
    if (GLEnv::CheckGLError("glGenBuffers")) return;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //glGetAttribLocation() to get location
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // 位置属性

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));//纹理坐标

    glBindVertexArray(0);

    unsigned int indices[] = {
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
    };

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    if (GLEnv::CheckGLError("glBufferData EBO")) return ;

    mTexture = std::make_shared<Texture>(activity->assetManager,"image/openxr.png",0);
    GLEnv::CheckGLError("Texture");
    std::string strVs = R"(
#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vTexCoord = aTexCoord;
}
)";

    std::string strFs = R"(
#version 300 es
precision mediump float;
out vec4 FragColor;
in vec2 vTexCoord;
uniform sampler2D sampler;
void main()
{
    FragColor = texture(sampler, vTexCoord);
}
)";

    mShader = std::make_shared<Shader>();
    mShader->setSource(strVs.c_str(), strFs.c_str());
    GLEnv::CheckGLError("Shader");
}

void TextureSample::onDraw() {

    if(mShader == nullptr || !mShader->useProgram()) return;

    mTexture->bind();

    mShader->setInt("sampler",0);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5f,0.6f,0.7f,1.0f);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    mShader->unuseProgram();
    GLEnv::CheckGLError("onDraw");
}