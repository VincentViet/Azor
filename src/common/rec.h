//
// Created by vice on 17/07/2019.
//

#ifndef AZOR_COMMON_REC_H_
#define AZOR_COMMON_REC_H_

struct Rectangle
{
    int x, y, width, height;
    Rectangle(int x, int y, int w, int h):
        x(x), y(y), width(w), height(h)
    {}
};

#endif //AZOR_SRC_COMMON_REC_H_
