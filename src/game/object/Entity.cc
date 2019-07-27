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
    if (m_body){
        b2Vec2 p = m_body->GetPosition();
        glm::vec2 pos(p.x, p.y);
        glm::vec2 result = pos - m_scene->getCamera()->getBound().min;

        if (m_sprite)
        {
            m_sprite->setPosition(result);
            m_sprite->setDirection(m_direction);
        }
    }
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
    : m_factor(1), m_tag(UNKNOWN)
{
    m_scene = scene;
    m_direction = 1;
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
void Entity::setDirection(int direction)
{
    m_direction = direction;
}
Entity::Entity(Scene *scene, const glm::vec2& factor)
{
    m_scene = scene;
    m_direction = 1;
    m_factor  = factor;
}
int Entity::getDirection() const
{
    return m_direction;
}
void Entity::onCollisionEnter(Entity *entity)
{}
void Entity::onCollisionExit(Entity *entity)
{}
Entity::Tag Entity::getTag()
{
    return m_tag;
}
