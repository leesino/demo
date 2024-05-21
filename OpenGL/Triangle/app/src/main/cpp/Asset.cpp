//
// Created by lixianru on 2024/5/14.
//

#include "Asset.h"


Asset::Asset(AAssetManager *assetManager, std::string path) : mAasset(nullptr) {
    mAasset = AAssetManager_open(assetManager, path.c_str(), AASSET_MODE_UNKNOWN);
}

const void *Asset::getBuffer() {
    if(mAasset == nullptr) return nullptr;
    return AAsset_getBuffer(mAasset);
}

int Asset::getBufferLength() {
    if(mAasset == nullptr) return 0;
    return AAsset_getLength(mAasset);
}

Asset::~Asset() {
    if(mAasset != nullptr){
        AAsset_close(mAasset);
        mAasset = nullptr;
    }
}