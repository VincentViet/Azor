//
// Created by vice on 18/07/2019.
//

#ifndef AZOR_CAMERA_CAMERA_H_
#define AZOR_CAMERA_CAMERA_H_

#include <glm/glm.hpp>
#include <renderer/Sprite.h>

class Camera
{
 private:
    glm::mat4 m_view{};
    glm::mat4 m_projection{};
    AABB m_bound;

 public:
    Camera(const glm::vec2& pos, int width, int height);

    glm::mat4& getView();
    glm::mat4& getProjection();
    const AABB& getBound();
    void  setPosition(const glm::vec2& pos);
};

#endif //AZOR_CAMERA_CAMERA_H_
