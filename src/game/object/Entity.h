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
    enum Tag{
        UNKNOWN,
        GROUND,
        CHARACTER
    };

    Body*               m_body{};
    Sprite*             m_sprite{};
    Scene*              m_scene;
    AABB                m_bound;
    int                 m_direction;
    glm::vec2           m_factor{};
    Tag                 m_tag;

 public:
    explicit            Entity(Scene* scene);
    explicit            Entity(Scene* scene, const glm::vec2& factor);
    virtual             ~Entity();

    virtual void        update();

    void                setActive(bool active);
    void                setDirection(int direction);
    int                 getDirection() const;
    bool                isActive() const;
    Body*               getBody();
    Sprite*             getSprite();
    virtual const AABB& getBound();
    Tag                 getTag();

    virtual void        onCollisionEnter(Entity* entity);
    virtual void        onCollisionExit(Entity* entity);
};

#endif //AZOR_SRC_GAME_OBJECT_ENTITY_H_
