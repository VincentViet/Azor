//
// Created by vice on 19/07/2019.
//

#ifndef AZOR_COMMON_TILE_H_
#define AZOR_COMMON_TILE_H_

#include <renderer/Sprite.h>
#include "game/Camera.h"

//struct Tile{
//    int id_;
//    Texture* texture_;
//    AABB layer_rect_;
//    AABB tile_rect_;
//    Tile(int id, Texture* texture,AABB  lr, AABB  tr)
//        : id_(id), texture_(texture), layer_rect_(lr), tile_rect_(tr){}
//};

class Tile : public Sprite{
    int m_id;
    AABB m_bound;
    Camera* m_camera;
    glm::vec2 m_factor;

 public:
    Tile(int id, Texture* texture, const AABB& bound, const AABB& rectangle);

    void setCamera(Camera* camera);
    void setFactor(const glm::vec2& factor);
    bool isValid() const;
    const AABB& getBound();
    glm::vec4* getData() override;
};

#endif //AZOR_COMMON_TILE_H_
