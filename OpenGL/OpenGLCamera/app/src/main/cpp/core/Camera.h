//
// Created by lixianru on 2024/6/26.
//

#ifndef CAMERA_CAMERA_H
#define CAMERA_CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <memory>

class Camera {
public:
    Camera();
    virtual ~Camera();
    glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();
private:
    glm::vec3 mPosition = glm::vec3(0.0f,0.0f,1.0f);
    glm::vec3 mUp = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 mRight = glm::vec3(1.0f,0.0f,0.0f);

};

class OrthographicCamera: public Camera{
public:
    OrthographicCamera(float left,
                       float right,
                       float top,
                       float bottom,
                       float near,
                       float far);
    ~OrthographicCamera();

    glm::mat4 getProjectionMatrix() override;

private:
    float mLeft{0.0f};
    float mRight{0.0f};
    float mTop{0.0f};
    float mBottom{0.0f};
    float mNear{0.0f};
    float mFar{0.0f};
};

class PerspectiveCamera: public Camera{
public:
    PerspectiveCamera(float fovy, float aspect, float near, float far);
    ~PerspectiveCamera();

    glm::mat4 getProjectionMatrix() override;
private:
    float mFovy{0.0f};
    float mAspect{0.0f};
    float mNear{0.0f};
    float mFar{0.0f};
};

#endif //CAMERA_CAMERA_H
