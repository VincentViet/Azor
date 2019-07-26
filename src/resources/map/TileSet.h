//
// Created by vice on 17/07/2019.
//

#ifndef AZOR_MAP_TILE_SET_H_
#define AZOR_MAP_TILE_SET_H_

#include <resources/Texture.h>
#include <common/AABB.h>

struct TileSet
{
    int first_id;
    int tile_count, tile_width, tile_height, columns;
    Texture* texture;

    AABB getRect(int id){
        int x = id % columns;
        int y = id / columns;
        int rows = tile_count / columns;

        AABB rect;
        rect.min = glm::vec2(x * tile_width, (rows - y) * tile_height);
        rect.max = rect.min + glm::vec2(tile_width, tile_height);

        return rect;
    }
};

#endif //AZOR_MAP_TILE_SET_H_
