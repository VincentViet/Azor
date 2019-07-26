//
// Created by vice on 26/07/2019.
//

#include "Ground.h"
Ground::Ground(float x, float y, float w, float h, Scene* scene)
    : Entity(scene)
{
    b2BodyDef body_def;
    body_def.position = b2Vec2(x + w * 0.5f, y + h * 0.5f);
    body_def.type = (b2BodyType)BodyType::STATIC;
    body_def.userData = this;

    b2PolygonShape box;
    box.SetAsBox(w * 0.5f, h * 0.5f);

    b2FixtureDef fixture_def;
    fixture_def.userData = this;
    fixture_def.density = 1;
    fixture_def.friction = 0;
    fixture_def.restitution = 0;
    fixture_def.shape = &box;

    m_body = physics::getWorld()->CreateBody(&body_def);
    m_body->CreateFixture(&fixture_def);
}