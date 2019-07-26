//
// Created by vice on 14/07/2019.
//

#ifndef AZOR_RES_H_
#define AZOR_RES_H_

#include <tinyxml2.h>
#include "Texture.h"
#include "map/Map.h"
#include "Shader.h"

namespace resources{
    void startUp(tinyxml2::XMLElement* resources);

    Texture* getTexture(const char* name);
    Map* getMap(const char* name);
    Shader* getShader(const char* name);

    void shutdown();
}

#endif //AZOR_RES_H_
