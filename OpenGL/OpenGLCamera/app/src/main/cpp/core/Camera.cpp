//
// Created by lixianru on 2024/6/26.
//

#include "Camera.h"
#include "utils/Log.h"


Camera::Camera(){
}
Camera::~Camera(){}




glm::mat4 Camera::getViewMatrix(){
    glm::vec3 front = glm::cross(mUp,mRight);
    glm::vec3 center = mPosition + front;
    return glm::lookAt(mPosition,center,mUp);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::identity<glm::mat4>();
}

OrthographicCamera::OrthographicCamera(float l,
                                       float r,
                                       float t,
                                       float b,
                                       float n,
                                       float f) :
                                       mLeft(l),
                                       mRight(r),
                                       mTop(t),
                                       mBottom(b),
                                       mNear(n),
                                       mFar(f){
}

OrthographicCamera::~OrthographicCamera() noexcept {}

glm::mat4 OrthographicCamera::getProjectionMatrix() {
    return glm::ortho(mLeft,mRight,mBottom,mTop,mNear,mFar);
}

PerspectiveCamera::PerspectiveCamera(float fovy,
                                     float aspect,
                                     float near,
                                     float far):mFovy(fovy),mAspect(aspect),mNear(near),mFar(far) {

}
PerspectiveCamera::~PerspectiveCamera() noexcept {

}

glm::mat4 PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(glm::radians(mFovy),mAspect,mNear,mFar);
}