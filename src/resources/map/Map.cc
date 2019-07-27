//
// Created by vice on 19/07/2019.
//

#include "Map.h"

#include <cstdlib>
#include <config.h>
#include <string>
#include <common/utils/string.h>
#include <resources/resources.h>
#include <game/scene.h>
#include <game/object/Ground.h>

#define TMX_DATA_TAG                                                                            "data"
#define TMX_LAYER_TAG                                                                           "layer"
#define TMX_OBJECT_TAG                                                                          "object"
#define TMX_TILE_SET_TAG                                                                        "tileset"
#define TMX_PROPERTY_TAG                                                                        "property"
#define TMX_OBJECT_GROUP_TAG                                                                    "objectgroup"
#define TMX_PROPERTIES_TAG                                                                      "properties"

#define TMX_X_ATTRIB                                                                            "x"
#define TMX_Y_ATTRIB                                                                            "y"
#define TMX_NAME_ATTRIB                                                                         "name"
#define TMX_WIDTH_ATTRIB                                                                        "width"
#define TMX_VALUE_ATTRIB                                                                        "value"
#define TMX_HEIGHT_ATTRIB                                                                       "height"
#define TMX_COLUMNS_ATTRIB                                                                      "columns"
#define TMX_FIRST_G_ID_ATTRIB                                                                   "firstgid"
#define TMX_TILE_WIDTH_ATTRIB                                                                   "tilewidth"
#define TMX_TILE_COUNT_ATTRIB                                                                   "tilecount"
#define TMX_TILE_HEIGHT_ATTRIB                                                                  "tileheight"

using namespace tinyxml2;

void Map::load()
{
    XMLDocument tmx;
    tmx.LoadFile(std::string(_AZOR_MAP_DIR_).append(m_path).c_str());

    tmx.RootElement()->QueryIntAttribute(TMX_WIDTH_ATTRIB, &m_width);
    tmx.RootElement()->QueryIntAttribute(TMX_HEIGHT_ATTRIB, &m_height);
    tmx.RootElement()->QueryIntAttribute(TMX_TILE_WIDTH_ATTRIB, &m_tile_width);
    tmx.RootElement()->QueryIntAttribute(TMX_TILE_HEIGHT_ATTRIB, &m_tile_height);

    m_tile_width *= m_factor.x;
    m_tile_height *= m_factor.y;

    m_bound = AABB(0, 0, (float)m_width * (float)m_tile_width, (float)m_height * (float)m_tile_height);

    loadTileSets(tmx);
    loadLayers(tmx);
}

static std::vector<int> getLayerData(const std::string& data){
    const auto& raw_data = string::split(data, ",");
    std::vector<int> result;

    result.reserve(raw_data.size());
    for (const auto& item: raw_data)
    {
        result.push_back(atoi(item.c_str()));
    }
    return result;
}

void Map::loadLayers(const XMLDocument& tmx)
{
    auto layer = tmx.RootElement()->FirstChildElement(TMX_LAYER_TAG);
    while (layer != nullptr){
        auto data = layer->FirstChildElement(TMX_DATA_TAG);
        std::string real_data(data->GetText());
        auto begin = real_data.begin();
        auto end = real_data.end();
        for (auto iter = begin; iter != end; iter++)
        {
            if(*iter == '\n')
                real_data.erase(iter);
        }

        const auto& ids = getLayerData(real_data);
        auto l = new Layer<Tile>;

        AABB lr, tr;
        Texture *texture = nullptr;
        glm::vec2 size(m_tile_width, m_tile_height);
        for (int row = 0; row < m_height; ++row)
            for (int col = 0; col < m_width; ++col)
            {
                lr.min = glm::vec2(col * m_tile_width, row * m_tile_height);
                lr.max = lr.min + size;

                int id = ids[row * m_width + col];
                id = id == 0 ? id : id - 1;
                for (auto& tile_set: m_tile_sets)
                {
                    int min = tile_set.first_id;
                    int max = tile_set.first_id + tile_set.tile_count;
                    if (min <= id && id <= max)
                    {
                        tr = tile_set.getRect(id);
                        texture = tile_set.texture;
                        break;
                    }
                }
                Tile tile(id, texture, lr, tr);
                tile.setFactor(m_factor);
                tile.setCamera(m_scene->getCamera());
                l->insert(tile);
            }

        m_tile_layers.emplace_back(l);
        layer = layer->NextSiblingElement(TMX_LAYER_TAG);
    }

    auto group = tmx.RootElement()->FirstChildElement(TMX_OBJECT_GROUP_TAG);
    while (group){
        Ground* ground;
        float x, y, width, height;
        auto object = group->FirstChildElement(TMX_OBJECT_TAG);
        auto l = new Layer<Entity*>;
        while (object){
            object->QueryFloatAttribute(TMX_X_ATTRIB, &x);
            object->QueryFloatAttribute(TMX_Y_ATTRIB, &y);
            object->QueryFloatAttribute(TMX_WIDTH_ATTRIB, &width);
            object->QueryFloatAttribute(TMX_HEIGHT_ATTRIB, &height);

            ground = new Ground(x, y, width, height, m_scene, m_factor);
            Entity* entity = ground;
            l->insert(entity);

            object = object->NextSiblingElement(TMX_OBJECT_TAG);
        }

        m_object_layers.emplace_back(l);
        group = group->NextSiblingElement(TMX_OBJECT_GROUP_TAG);
    }
}
void Map::loadTileSets(const XMLDocument& tmx)
{
    const char *source, *name;
    XMLDocument tsx;

    auto tmx_root = tmx.RootElement();

    TileSet set{};
    auto tile_set = tmx_root->FirstChildElement(TMX_TILE_SET_TAG);
    while (tile_set != nullptr){
        tile_set->QueryStringAttribute("source", &source);
        tile_set->QueryIntAttribute(TMX_FIRST_G_ID_ATTRIB, &set.first_id);

        tsx.LoadFile(std::string(_AZOR_MAP_DIR_).append(source).c_str());

        tsx.RootElement()->QueryIntAttribute(TMX_TILE_WIDTH_ATTRIB, &set.tile_width);
        tsx.RootElement()->QueryIntAttribute(TMX_TILE_HEIGHT_ATTRIB, &set.tile_height);
        tsx.RootElement()->QueryIntAttribute(TMX_TILE_COUNT_ATTRIB, &set.tile_count);
        tsx.RootElement()->QueryIntAttribute(TMX_COLUMNS_ATTRIB, &set.columns);
        tsx.RootElement()->QueryStringAttribute(TMX_NAME_ATTRIB, &name);

        set.texture = resources::getTexture(name);
        m_tile_sets.emplace_back(set);

        tile_set = tile_set->NextSiblingElement(TMX_TILE_SET_TAG);
    }
}
Layer<Tile>* Map::getTileLayer(int id)
{
    return m_tile_layers.at(id);
}
Map::~Map()
{
    for (auto layer: m_tile_layers)
    {
        delete layer;
    }
}
void Map::setScene(Scene *scene)
{
    m_scene = scene;
}
Map::Map(const char *path)
    : m_scene(nullptr), m_path(path), m_factor(1.0)
{}
Layer<Entity *> *Map::getObjectLayer(int id)
{
    return m_object_layers.at(id);
}
void Map::setFactor(const glm::vec2 &factor)
{
    m_factor = factor;
}
AABB &Map::getBound()
{
    return m_bound;
}
