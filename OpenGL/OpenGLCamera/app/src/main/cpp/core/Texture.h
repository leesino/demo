//
// Created by lixianru on 2024/5/18.
//

#ifndef OPENGLTEXTURE_TEXTURE_H
#define OPENGLTEXTURE_TEXTURE_H


#include "Asset.h"

class Texture {
public:
    Texture(AAssetManager *assetManager, std::string path, int unit);
    ~Texture();

    void bind();
private:

    int mUint {0};
    unsigned int mTexture{0};

};


#endif //OPENGLTEXTURE_TEXTURE_H
