//
// Created by lixianru on 2024/5/17.
//
#include "Object.h"
#include "CameraSample.h"

ANativeActivity* Object::activity;

Object *Object::createObject(std::string name) {
    if(name == "camera"){
        return new CameraSample();
    }

    return nullptr;
}
