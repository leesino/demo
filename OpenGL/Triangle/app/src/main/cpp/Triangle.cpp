//
// Created by lixianru on 2024/5/14.
//

#include "Triangle.h"
#include "Asset.h"
#include "Log.h"
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

Triangle::Triangle(ANativeActivity *activity) {
    mActivity = activity;
    VBO = 0;
    VAO = 0;
}

Triangle::~Triangle(){
    if(VAO != 0){
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if(VBO != 0){
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

}

void Triangle::init(){
    //prepare data
    float vertices[] = {
            // 位置信息         // 颜色信息
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // 左下
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // 顶部
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // 位置属性

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));// 颜色属性
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    //prepare command
    Asset vsAsset = Asset(mActivity->assetManager,"shader/triangle.vs");
    Asset fsAsset = Asset(mActivity->assetManager,"shader/triangle.fs");
    std::string strVs((char *) (const void *) vsAsset.getBuffer(),(size_t)vsAsset.getBufferLength());
    std::string strFs((char *) (const void *) fsAsset.getBuffer(),(size_t)fsAsset.getBufferLength());
    mShader = std::make_shared<Shader>();
    mShader->setSource(strVs.c_str(), strFs.c_str());
}

void Triangle::onDraw() {
    if(mShader == nullptr || !mShader->useProgram()) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f,0.6f,0.7f,1.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFlush();

    mShader->unuseProgram();
}