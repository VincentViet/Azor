//
// Created by vice on 26/07/2019.
//

#include "physics.h"
#include "DebugDraw.h"
#include "ContactListener.h"
#include <config.h>

static World* world = nullptr;
static DebugDraw* debug;
static ContactListener* listener;

void physics::startUp(tinyxml2::XMLElement *world_node)
{
    b2Vec2 gravity(0, 0);
    world_node->QueryFloatAttribute(_AZOR_CONFIG_PHYSICS_WORLD_GRAVITY_ATTRIB_, &gravity.y);
    world = new World(gravity);

    debug = new DebugDraw;
    listener = new ContactListener;
    debug->SetFlags(b2Draw::e_aabbBit | b2Draw::e_shapeBit);
    world->SetDebugDraw(debug);

    world->SetContactListener(listener);
}

void physics::update()
{
    static const float time_step = 1.0f / 120.0f;
    world->Step(time_step, 6, 2);
}

void physics::draw()
{
    world->DrawDebugData();
}

World* physics::getWorld()
{
    return world;
}

void physics::shutdown()
{
    delete debug;
    delete listener;
    delete world;
}