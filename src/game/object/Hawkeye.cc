//
// Created by vice on 26/07/2019.
//

#include "Hawkeye.h"
#include <window/window.h>
#include <game/scene.h>
#include <debug/dbg.h>

#define ANIMATION_DURATION 0.15f

static void idle(Entity* entity);
static void moveLeft(Entity* entity);
static void moveRight(Entity* entity);
static void jump(Entity* entity);

static AABB animation[6]{
    {57.875, 311.875, 22.25, 45.375},
    {88, 312, 23, 44.25},
    {120.875, 312, 18.25, 45},
    {151.75, 311.875, 22.625, 44.625},
    {185.25, 312.25, 17.625, 44.625},
    {15.5, 197, 24.5, 40}
};
static float speed = 1000.0f;
static bool    m_is_grounded;

Hawkeye::Hawkeye(Scene *scene)
    : Entity(scene, {4.0f, 4.0f})
{
    b2BodyDef body_def;
    body_def.position = b2Vec2(47 * m_factor.x, 840 * m_factor.y);
    body_def.type = (b2BodyType)BodyType::DYNAMIC;
    body_def.fixedRotation = true;
    body_def.userData = this;

    b2PolygonShape box;
    box.SetAsBox(12.5 * m_factor.x, 23 * m_factor.y);

    b2FixtureDef fixture_def;
    fixture_def.userData = this;
    fixture_def.density = 1;
    fixture_def.friction = 0;
    fixture_def.restitution = 0;
    fixture_def.shape = &box;

    m_body = physics::getWorld()->CreateBody(&body_def);
    m_body->CreateFixture(&fixture_def);

    m_sprite = new Sprite("hawkeye");
    m_sprite->setFactor(m_factor);

    m_brand.pushState(idle);
    m_direction = -1;
    m_tag = CHARACTER;
    m_is_grounded = false;
}
void Hawkeye::update()
{
    auto state = m_brand.getCurrentState();
    if (state)
        state(this);

    Entity::update();
}
FSM &Hawkeye::getFSM()
{
    return m_brand;
}
void Hawkeye::onCollisionEnter(Entity *entity)
{
    m_is_grounded = entity->getTag() == GROUND;
}

void animateWalk(Entity* entity){
    static int anim = 0;
    static float duration = 0.0f;
    duration += (float)window::getDeltaTime();
    if (duration >= ANIMATION_DURATION)
    {
        anim = anim > 3 ? 0 : anim + 1;
        duration = 0.0f;
    }
    entity->getSprite()->setRectangle(animation[anim]);
}

void moveLeft(Entity* entity)
{
    FSM& fsm = ((Hawkeye*)entity)->getFSM();
    auto v = entity->getBody()->GetLinearVelocity();

    if (window::isKeyDown(window::Keys::LEFT))
    {
        entity->getBody()->SetLinearVelocity(b2Vec2(-speed, v.y));
        entity->setDirection(1);
        animateWalk(entity);
    }
    else if (window::isKeyDown(window::Keys::RIGHT))
    {
        fsm.popState();
        fsm.pushState(moveRight);
    } else if (window::isKeyDown(window::Keys::X) && m_is_grounded){
        fsm.popState();
        fsm.pushState(jump);
    }else{
        fsm.popState();
    }
}
void moveRight(Entity* entity)
{
    FSM& fsm = ((Hawkeye*)entity)->getFSM();
    auto v = entity->getBody()->GetLinearVelocity();

    if (window::isKeyDown(window::Keys::RIGHT))
    {
        entity->getBody()->SetLinearVelocity(b2Vec2(speed, v.y));
        entity->setDirection(-1);
        animateWalk(entity);
    }
    else if (window::isKeyDown(window::Keys::LEFT))
    {
        fsm.popState();
        fsm.pushState(moveLeft);
    } else if (window::isKeyDown(window::Keys::X) && m_is_grounded){
        fsm.popState();
        fsm.pushState(jump);
    }
    else{
        fsm.popState();
    }
}
void idle(Entity* entity)
{
    auto v = entity->getBody()->GetLinearVelocity();
    entity->getBody()->SetLinearVelocity(b2Vec2(0, v.y));

    entity->getSprite()->setRectangle(animation[0]);
    entity->setDirection(entity->getDirection());

    FSM& fsm = ((Hawkeye*)entity)->getFSM();

    if (window::isKeyDown(window::Keys::LEFT))
        fsm.pushState(moveLeft);
    else if (window::isKeyDown(window::Keys::RIGHT))
        fsm.pushState(moveRight);
    else if (window::isKeyDown(window::Keys::X) && m_is_grounded){
        fsm.pushState(jump);
    }
}
void jump(Entity* entity){
    auto direction = entity->getDirection();
    entity->getBody()->ApplyForceToCenter(b2Vec2(100 * -direction, -1000), true);
    entity->getSprite()->setRectangle(animation[5]);

    FSM& fsm = ((Hawkeye*)entity)->getFSM();
    if (m_is_grounded){
        fsm.popState();
    }
}