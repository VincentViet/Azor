//
// Created by vice on 26/07/2019.
//

#include "physics.h"
#include <config.h>

static World* world = nullptr;

void physics::startUp(tinyxml2::XMLElement *world_node)
{
    b2Vec2 gravity(0, 0);
    world_node->QueryFloatAttribute(_AZOR_CONFIG_PHYSICS_WORLD_GRAVITY_ATTRIB_, &gravity.y);
    world = new World(gravity);
}

void physics::update()
{
    static const float time_step = 1.0f / 60.0f;
    world->Step(time_step, 6, 2);
}

World* physics::getWorld()
{
    return world;
}

void physics::shutdown()
{
    delete world;
}