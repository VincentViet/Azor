//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_GAME_OBJECT_GROUND_H_
#define AZOR_SRC_GAME_OBJECT_GROUND_H_

#include "Entity.h"

class Ground : public Entity
{
 public:
    Ground(float x, float y, float w, float h, Scene* scene);
};

#endif //AZOR_SRC_GAME_OBJECT_GROUND_H_
