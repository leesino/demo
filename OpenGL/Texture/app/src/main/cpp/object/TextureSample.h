//
// Created by lixianru on 2024/5/17.
//

#ifndef OPENGLTEXTURE_TEXTURESAMPLE_H
#define OPENGLTEXTURE_TEXTURESAMPLE_H
#include "Object.h"
#include "core/Texture.h"
#include <core/Shader.h>
class TextureSample : public Object{
public:
    TextureSample();
    ~TextureSample();

    void init() override;
    void onDraw() override;

private:
    unsigned int VBO, VAO, EBO;
    std::shared_ptr<Shader> mShader;
    std::shared_ptr<Texture> mTexture;
};


#endif //OPENGLTEXTURE_TEXTURESAMPLE_H
