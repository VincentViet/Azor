//
// Created by vice on 26/07/2019.
//

#include "Ground.h"
Ground::Ground(float x, float y, float w, float h, Scene *scene, const glm::vec2 &factor)
    : Entity(scene, factor)
{
    b2BodyDef body_def;
    body_def.position = b2Vec2((x + w * 0.5f) * m_factor.x, (y + h * 0.5f) * m_factor.y);
    body_def.type = (b2BodyType)BodyType::STATIC;
    body_def.userData = this;

    b2PolygonShape box;
    box.SetAsBox(w * 0.5f * m_factor.x, h * 0.5f * m_factor.y);

    b2FixtureDef fixture_def;
    fixture_def.userData = this;
    fixture_def.density = 1;
    fixture_def.friction = 0;
    fixture_def.restitution = 0;
    fixture_def.shape = &box;

    m_body = physics::getWorld()->CreateBody(&body_def);
    m_body->CreateFixture(&fixture_def);
    m_tag = GROUND;
}
