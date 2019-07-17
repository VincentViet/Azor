//
// Created by vice on 17/07/2019.
//

#ifndef AZOR_TMXPARSER_H_
#define AZOR_TMXPARSER_H_

#include "map.h"

namespace tmx{
    Map* parse(const char* path);
}

#endif //AZOR_TMXPARSER_H_
