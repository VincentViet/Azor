//
// Created by vice on 15/07/2019.
//

#ifndef AZOR_SRC_RES_TEXTURE_H_
#define AZOR_SRC_RES_TEXTURE_H_

struct Texture{
    int id;
    int width;
    int height;

    Texture(int id, int width, int height)
        :id(id), width(width), height(height){}
    void bind();
};

#endif //AZOR_SRC_RES_TEXTURE_H_
