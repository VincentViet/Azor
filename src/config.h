//
// Created by vice on 14/07/2019.
//

#ifndef _AZOR_CONF_H_
#define _AZOR_CONF_H_

#define _AZOR_DEFAULT_VERTEX_SHADER_                    "../shaders/default.vert"
#define _AZOR_DEFAULT_FRAGMENT_SHADER_                  "../shaders/default.frag"

#define _AZOR_RESOURCE_ROOT_                            "../resources/"
#define _AZOR_MAP_DIR_                                  _AZOR_RESOURCE_ROOT_  "maps/"
#define _AZOR_TILE_SET_DIR_                             _AZOR_MAP_DIR_ "tilesets/"
#define _AZOR_IMAGES_DIR_                               _AZOR_RESOURCE_ROOT_ "images/"
#define _AZOR_SHADERS_DIR_                              _AZOR_RESOURCE_ROOT_ "shaders/"
#define _AZOR_CONFIG_FILE_                              _AZOR_RESOURCE_ROOT_ "app.config.xml"

// CONFIG FILE
#define _AZOR_CONFIG_ROOT_TAG_                          "app"
#define _AZOR_CONFIG_MAP_TAG_                           "map"
#define _AZOR_CONFIG_SHADER_TAG_                        "shader"

#define _AZOR_CONFIG_NAME_ATTRIB                        "name"
#define _AZOR_CONFIG_WIDTH_ATTRIB                       "width"
#define _AZOR_CONFIG_HEIGHT_ATTRIB                      "height"

// LOGGING
#define _AZOR_CONFIG_LOGGING_TAG_                       "logging"
#define _AZOR_CONFIG_LOGGING_PATTERN_ATTRIB_            "pattern"
#define _AZOR_CONFIG_LOGGING_LEVEL_ATTRIB_              "level"
// END LOGGING

// WINDOW
#define _AZOR_CONFIG_WINDOW_TAG_                        "window"
#define _AZOR_CONFIG_WINDOW_WIDTH_ATTRIB_               _AZOR_CONFIG_WIDTH_ATTRIB
#define _AZOR_CONFIG_WINDOW_HEIGHT_ATTRIB_              _AZOR_CONFIG_HEIGHT_ATTRIB
#define _AZOR_CONFIG_WINDOW_TITLE_ATTRIB_               "title"
#define _AZOR_CONFIG_WINDOW_CENTER_SCREEN_ATTRIB_       "centerScreen"
// END WINDOW

// RENDERER
#define _AZOR_CONFIG_RENDERER_TAG_                      "renderer"
#define _AZOR_CONFIG_RENDERER_VIEWPORT_ATTRIB_          "viewport"
// END RENDERER

// RESOURCES
#define _AZOR_CONFIG_RESOURCES_TAG_                     "resources"
#define _AZOR_CONFIG_RESOURCES_IMG_TAG_                 "img"
#define _AZOR_CONFIG_RESOURCES_IMAGES_TAG_              "images"
#define _AZOR_CONFIG_RESOURCES_SHADER_TAG_              _AZOR_CONFIG_SHADER_TAG_
#define _AZOR_CONFIG_RESOURCES_PROGRAM_TAG_             "program"
#define _AZOR_CONFIG_RESOURCES_SHADER_PROGRAM_TAG_      "shaderPrograms"
#define _AZOR_CONFIG_RESOURCES_MAP_TAG_                 _AZOR_CONFIG_MAP_TAG_
#define _AZOR_CONFIG_RESOURCES_MAPS_TAG_                "maps"

#define _AZOR_CONFIG_RESOURCES_SRC_ATTRIB_              "src"
#define _AZOR_CONFIG_RESOURCES_NAME_ATTRIB_             _AZOR_CONFIG_NAME_ATTRIB
#define _AZOR_CONFIG_RESOURCES_TYPE_ATTRIB_             "type"
// END RESOURCES

// SCENES
#define _AZOR_CONFIG_SCENE_TAG_                         "scene"
#define _AZOR_CONFIG_SCENES_TAG_                        "scenes"
#define _AZOR_CONFIG_SCENES_MAP_TAG_                    _AZOR_CONFIG_MAP_TAG_
#define _AZOR_CONFIG_SCENES_CAMERA_TAG_                 "camera"
#define _AZOR_CONFIG_SCENES_SHADER_TAG_                 _AZOR_CONFIG_SHADER_TAG_

#define _AZOR_CONFIG_SCENES_NAME_ATTRIB_                _AZOR_CONFIG_NAME_ATTRIB
#define _AZOR_CONFIG_SCENES_WIDTH_ATTRIB                _AZOR_CONFIG_WIDTH_ATTRIB
#define _AZOR_CONFIG_SCENES_HEIGHT_ATTRIB               _AZOR_CONFIG_HEIGHT_ATTRIB
#define _AZOR_CONFIG_SCENES_FIRST_SCENE_ATTRIB          "firstScene"
// END SCENES

// PHYSICS
#define _AZOR_CONFIG_PHYSICS_WORLD_TAG_                 "physicsWorld"
#define _AZOR_CONFIG_PHYSICS_WORLD_GRAVITY_ATTRIB_      "gravity"
// END PHYSICS

// END CONFIG FILE
#endif //_AZOR_CONF_H_
