//
// Created by vice on 27/07/2019.
//

#ifndef AZOR_SRC_PHYSICS_CONTACTLISTENER_H_
#define AZOR_SRC_PHYSICS_CONTACTLISTENER_H_

#include <Box2D/Box2D.h>

class ContactListener: public b2ContactListener
{
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};

#endif //AZOR_SRC_PHYSICS_CONTACTLISTENER_H_
