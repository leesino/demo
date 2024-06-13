//
// Created by lixianru on 2024/5/17.
//
#include "Object.h"
#include "TransformSample.h"

ANativeActivity* Object::activity;

Object *Object::createObject(std::string name) {
    if(name == "texture"){
        return new TransformSample();
    }

    return nullptr;
}
