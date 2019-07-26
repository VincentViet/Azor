//
// Created by vice on 17/07/2019.
//

#ifndef AZOR_TMXPARSER_MAP_H_
#define AZOR_TMXPARSER_MAP_H_

#include "Tile.h"
#include "TileSet.h"
#include "Layer.h"
#include "tinyxml2.h"
#include <game/object/Entity.h>
#include <string>

class Scene;

class Map
{
    int m_width{};
    int m_height{};
    int m_tile_width{};
    int m_tile_height{};
    Scene* m_scene;
    std::string m_path{};

    std::vector<TileSet> m_tile_sets;
    std::vector<Layer<Tile>*> m_tile_layers;
    std::vector<Layer<Entity*>*> m_object_layers{};

    friend class Scene;
 private:
    void loadLayers(const tinyxml2::XMLDocument& tmx);
    void loadTileSets(const tinyxml2::XMLDocument& tmx);
 public:
    explicit Map(const char* path);
    ~Map();
    void load();
    void setScene(Scene* scene);
    Layer<Tile>* getTileLayer(int id);
    Layer<Entity*>* getObjectLayer(int id);
};

#endif //AZOR_TMXPARSER_MAP_H_
