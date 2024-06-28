//
// Created by lixianru on 2024/5/17.
//

#include "CameraSample.h"
#include "core/GLEnv.h"
#include "utils/Log.h"
#include <core/Asset.h>
#include <core/Texture.h>



CameraSample::CameraSample() {
    VAO = VBO = EBO = 0;
 //scale ,rotation, translate
    cubes.push_back(Transform{{-1.5,-0.5,-3}, {0.5f, 0.5f, 0.5f}});//25cm
    cubes.push_back(Transform{{0,0,-3}, {0.5f, 0.5f, 0.5f}});
    cubes.push_back(Transform{{1.5,0.8,-3}, {0.55f, 0.55f, 0.55f}});
}

CameraSample::~CameraSample() {
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

void CameraSample::init(int width, int height) {
    mWidth = width;
    mHeight = height;

// The version statement has come on first line.
    static const char* strVs = R"_(#version 300 es

    in vec3 VertexPos;
    in vec3 VertexColor;
    out vec3 PSVertexColor;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
       gl_Position = projection * view * model * vec4(VertexPos, 1.0);
       PSVertexColor = VertexColor;
    }
    )_";
//
// The version statement has come on first line.
    static const char* strFs = R"_(#version 300 es
    in lowp vec3 PSVertexColor;
    out lowp vec4 FragColor;

    void main() {
       FragColor = vec4(PSVertexColor, 1);
    }
    )_";

    mShader = std::make_shared<Shader>();
    mShader->setSource(strVs, strFs);

    auto coordsLocation = mShader->getAttribLocation("VertexPos");
    auto colorLocation = mShader->getAttribLocation("VertexColor");

    //init VBO VAO EBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(c_cubeVertices), c_cubeVertices, GL_STATIC_DRAW);
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(c_cubeIndices), c_cubeIndices, GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    LOGI("TransformSample::init coordsLocation %d colorLocation %d",coordsLocation,colorLocation);
    glEnableVertexAttribArray(coordsLocation);
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(coordsLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<const void*>(sizeof(glm::vec3)));
}

void CameraSample::onDraw(Camera *camera) {
    if(mShader == nullptr || !mShader->useProgram() || camera == nullptr) return;
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f,0.6f,0.7f,1.0f);
    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    mShader->useProgram();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    mShader->setMatrix4f("view", view);
    mShader->setMatrix4f("projection", projection);
    static float angle = 0;
    int i = 0;
    for(auto cube: cubes){
       //pass  identity matrix
       glm::mat4 model(1.0f);
       model = glm::translate(model,cube.Pose);
       model = glm::scale(model, cube.Scale);
//       if(i%3==0){
//           model = glm::rotate(model,glm::radians(angle),glm::vec3(1,0,0));
//       }else if(i%3 == 1){
//           model = glm::rotate(model,glm::radians(angle),glm::vec3(0,1,0));
//       }else{
//           model = glm::rotate(model,glm::radians(angle),glm::vec3(0,0,1));
//       }
//       i++;
       mShader->setMatrix4f("model", model);
       glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
    }
    angle += 1;
    glFlush();
    mShader->unuseProgram();
}