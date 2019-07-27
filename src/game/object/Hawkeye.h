//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_GAME_OBJECT_HAWKEYE_H_
#define AZOR_SRC_GAME_OBJECT_HAWKEYE_H_

#include "Entity.h"
#include <common/FSM.h>

class Hawkeye : public Entity
{
    FSM     m_brand;
 public:
    explicit Hawkeye(Scene* scene);
    void update() override;
    FSM& getFSM();

    void onCollisionEnter(Entity* entity) override;
};

#endif //AZOR_SRC_GAME_OBJECT_HAWKEYE_H_
