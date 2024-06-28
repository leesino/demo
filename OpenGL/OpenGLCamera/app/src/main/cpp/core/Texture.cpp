//
// Created by lixianru on 2024/5/18.
//

#include "Texture.h"
#include "utils/Log.h"
#include "GLEnv.h"

#define STB_IMAGE_IMPLEMENTATION
#include <utils/stb_image.h>
#include <GLES3/gl3.h>

Texture::Texture(AAssetManager *assetManager, std::string path, int unit) {
    mUint = unit;
    mTexture = 0;
    glGenTextures(1, &mTexture);
    LOGI("Texture::Texture mTexture %d", mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);//only set this will affect to the texture object
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //setdata
    int w = 0,h = 0, n = 0;

    AAsset *pathAsset = AAssetManager_open(assetManager,path.c_str(), AASSET_MODE_BUFFER);
    unsigned char *filedata = (unsigned char *) AAsset_getBuffer(pathAsset);
    off_t assetLength = AAsset_getLength(pathAsset);
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load_from_memory(filedata, assetLength,&w,&h,&n,0);
    if(data != nullptr){
        GLint format = GL_RGB;
        if(n == 4) format = GL_RGBA;

        LOGI("Texture::Texture w %d h %d n %d data %p", w,h, n, data);
        glTexImage2D(GL_TEXTURE_2D,0, format, w,h,0,format,GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
}
Texture::~Texture() {
    if(mTexture != 0){
        glDeleteTextures(1, &mTexture);
    }
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0+mUint);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}
