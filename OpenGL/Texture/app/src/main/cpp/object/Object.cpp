//
// Created by lixianru on 2024/5/17.
//
#include "Object.h"
#include "TextureSample.h"

ANativeActivity* Object::activity;

Object *Object::createObject(std::string name) {
    if(name == "texture"){
        return new TextureSample();
    }

    return nullptr;
}
