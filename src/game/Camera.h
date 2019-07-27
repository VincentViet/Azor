//
// Created by vice on 18/07/2019.
//

#ifndef AZOR_CAMERA_CAMERA_H_
#define AZOR_CAMERA_CAMERA_H_

#include <glm/glm.hpp>
#include "object/Entity.h"
#include <renderer/Sprite.h>

class Camera
{
 private:
    glm::mat4   m_view{};
    glm::mat4   m_projection{};
    AABB        m_bound;
    AABB        m_clamp;
    Entity*     m_followed;

 public:
    Camera(const glm::vec2& pos, int width, int height);

    void            setClamp(const AABB& aabb);
    glm::mat4&      getView();
    glm::mat4&      getProjection();
    const AABB&     getBound();
    void            setPosition(const glm::vec2& pos);
    void            followed(Entity* entity);

    void            update();
};

#endif //AZOR_CAMERA_CAMERA_H_
