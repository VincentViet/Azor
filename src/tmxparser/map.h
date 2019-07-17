//
// Created by vice on 17/07/2019.
//

#ifndef AZOR_TMXPARSER_MAP_H_
#define AZOR_TMXPARSER_MAP_H_

#include "tileset.h"

namespace tmx{
struct Map
{
    int width;
    int height;
    int tile_width;
    int tile_height;

    std::vector<TileSet> sets;
    std::vector<std::vector<int>> layers;
};
}

#endif //AZOR_TMXPARSER_MAP_H_
