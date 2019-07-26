//
// Created by vice on 24/07/2019.
//

#ifndef AZOR_SRC_RENDERER_RENDERER_H_
#define AZOR_SRC_RENDERER_RENDERER_H_

#include <tinyxml2.h>
#include "SpriteBatch.h"

namespace renderer{
    void startUp(tinyxml2::XMLElement* renderer);
    void update();
    SpriteBatch* getSpriteBatch();
    void shutdown();
}

#endif //AZOR_SRC_RENDERER_RENDERER_H_
