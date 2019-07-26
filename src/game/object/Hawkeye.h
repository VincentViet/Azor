//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_GAME_OBJECT_HAWKEYE_H_
#define AZOR_SRC_GAME_OBJECT_HAWKEYE_H_

#include "Entity.h"
class Hawkeye : public Entity
{
 public:
    explicit Hawkeye(Scene* scene);
    void update() override;
};

#endif //AZOR_SRC_GAME_OBJECT_HAWKEYE_H_
