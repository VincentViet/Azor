//
// Created by vice on 18/07/2019.
//

#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec2 &position, int width, int height)
    : view_(1.0), pos_(position)
{
    map_ = nullptr;
    this->half_width_ = width / 2;
    this->half_height_ = height / 2;
    glm::translate(view_, glm::vec3(position, 0.0f));
}
void Camera::set_map(tmx::Map *map)
{
    this->map_ = map;
}
const glm::mat4 &Camera::get_view_matrix() const
{
    return this->view_;
}
void Camera::set_position(const glm::vec2 &pos)
{
    pos_ = pos;
    glm::translate(this->view_, glm::vec3(pos, 0.0f));
}
std::vector<Sprite> Camera::get_sprites() const
{

    return std::vector<Sprite>();
}
