//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_PHYSICS_PHYSICS_H_
#define AZOR_SRC_PHYSICS_PHYSICS_H_

#include <Box2D/Box2D.h>
#include <tinyxml2.h>

typedef b2Body  Body;
typedef b2Vec2  Vec2;
typedef b2World World;

enum class BodyType{
    STATIC = b2_staticBody,
    KINEMATIC = b2_kinematicBody,
    DYNAMIC = b2_dynamicBody,
};

namespace physics{
    void startUp(tinyxml2::XMLElement* world);
    void update();
    void shutdown();
    World* getWorld();
}

#endif //AZOR_SRC_PHYSICS_PHYSICS_H_
