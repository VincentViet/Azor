//
// Created by vice on 26/07/2019.
//

#include "Hawkeye.h"
Hawkeye::Hawkeye(Scene *scene)
    : Entity(scene)
{
    b2BodyDef body_def;
    body_def.position = b2Vec2(640, 400);
    body_def.type = (b2BodyType)BodyType::DYNAMIC;
    body_def.userData = this;

    b2PolygonShape box;
    box.SetAsBox(50, 100);

    b2FixtureDef fixture_def;
    fixture_def.userData = this;
    fixture_def.density = 1;
    fixture_def.friction = 0;
    fixture_def.restitution = 0;
    fixture_def.shape = &box;

    m_body = physics::getWorld()->CreateBody(&body_def);
    m_body->CreateFixture(&fixture_def);

    m_sprite = new Sprite("hawkeye");
    m_sprite->setRectangle(AABB(0, 0, 50, 100));
}
void Hawkeye::update()
{
    auto pos = m_body->GetPosition();
    m_sprite->setPosition(glm::vec2(pos.x, pos.y));
}
