//
// Created by vice on 18/07/2019.
//

#ifndef AZOR_CAMERA_CAMERA_H_
#define AZOR_CAMERA_CAMERA_H_

#include <glm/glm.hpp>
#include <render/sprite.h>
#include <tmxparser/map.h>

class Camera
{
 private:
    int half_width_;
    int half_height_;
    tmx::Map* map_;
    glm::mat4 view_;
    glm::vec2 pos_;

 public:
    Camera(const glm::vec2& position, int width, int height);
    void set_map(tmx::Map* map);
    const glm::mat4& get_view_matrix() const;
    void  set_position(const glm::vec2& pos);
    std::vector<Sprite> get_sprites() const;
};

#endif //AZOR_CAMERA_CAMERA_H_
