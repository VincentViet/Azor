//
// Created by vice on 27/07/2019.
//

#include "ContactListener.h"
#include <game/object/Entity.h>

void ContactListener::BeginContact(b2Contact *contact)
{
    auto e_a = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto e_b = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (e_a)
        e_a->onCollisionEnter(e_b);
    if (e_b)
        e_b->onCollisionEnter(e_a);
}
void ContactListener::EndContact(b2Contact *contact)
{
    auto e_a = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto e_b = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (e_a)
        e_a->onCollisionExit(e_b);
    if (e_b)
        e_b->onCollisionExit(e_a);
}
