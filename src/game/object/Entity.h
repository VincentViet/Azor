//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_GAME_OBJECT_ENTITY_H_
#define AZOR_SRC_GAME_OBJECT_ENTITY_H_

#include <physics/physics.h>
#include <renderer/Sprite.h>
#include <common/AABB.h>

class Scene;

class Entity
{
 protected:
    Body*               m_body{};
    Sprite*             m_sprite{};
    Scene*              m_scene;
    AABB                m_bound;
    int                 m_direction;
 public:
    explicit            Entity(Scene* scene);
    virtual             ~Entity();

    virtual void        update();

    void                setActive(bool active);
    void                setDirection(int direction);
    bool                isActive() const;
    Body*               getBody();
    Sprite*             getSprite();
    virtual const AABB& getBound();
};

#endif //AZOR_SRC_GAME_OBJECT_ENTITY_H_
