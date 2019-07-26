//
// Created by vice on 26/07/2019.
//

#include "Entity.h"
#include <game/scene.h>

Entity::~Entity()
{
    delete m_sprite;
}
void Entity::update()
{
//    if (m_body){
//        b2Vec2 pos = m_body->GetPosition();
//        glm::vec2 glm_pos(pos.x, pos.y);
//        glm::vec2 camera_pos = m_scene->getCamera()->getBound().getPos();
//        glm::vec2 result = glm_pos - camera_pos;
//
//        m_body->SetTransform(b2Vec2(result.x, result.y), 0);
//    }
}
Body *Entity::getBody()
{
    return m_body;
}
Sprite *Entity::getSprite()
{
    return m_sprite;
}
Entity::Entity(Scene *scene)
{
    m_scene = scene;
}
void Entity::setActive(bool active)
{
    m_body->SetActive(active);
}
bool Entity::isActive() const
{
    return m_body->IsActive();
}
const AABB &Entity::getBound()
{
    auto pos = m_body->GetPosition();
    m_bound.setPos(glm::vec2(pos.x, pos.y));
    return m_bound;
}
