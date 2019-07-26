//
// Created by vice on 24/07/2019.
//

#include "logging.h"
#include <config.h>

void logging::startUp(tinyxml2::XMLElement *logging)
{
    int level;
    const char* pattern;
    if (logging){
        logging->QueryIntAttribute(_AZOR_CONFIG_LOGGING_LEVEL_ATTRIB_, &level);
        logging->QueryStringAttribute(_AZOR_CONFIG_LOGGING_PATTERN_ATTRIB_, &pattern);

        spdlog::set_level((spdlog::level::level_enum)level);
        spdlog::set_pattern(pattern);
    }
}
