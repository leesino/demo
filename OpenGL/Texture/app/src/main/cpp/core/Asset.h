//
// Created by lixianru on 2024/5/14.
//

#ifndef OPENGLTRIANGLE_ASSET_H
#define OPENGLTRIANGLE_ASSET_H

#include <string>
#include <android/asset_manager.h>

class Asset {
public:
    Asset(AAssetManager* assetManager,std::string path);
    ~Asset();
    const void*getBuffer();
    int getBufferLength();
private:
    AAsset *mAasset;
};


#endif //OPENGLTRIANGLE_ASSET_H
