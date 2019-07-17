//
// Created by vice on 17/07/2019.
//

#include "tmxparser.h"
#include <cstdlib>
#include <azor-conf.h>
#include <res/res.h>
#include <tinyxml2/tinyxml2.h>

#define TMX_DATA_TAG                                                                            "data"
#define TMX_LAYER_TAG                                                                           "layer"
#define TMX_TILE_SET_TAG                                                                        "tileset"

#define TMX_NAME_ATTRIB                                                                         "name"
#define TMX_WIDTH_ATTRIB                                                                        "width"
#define TMX_HEIGHT_ATTRIB                                                                       "height"
#define TMX_COLUMNS_ATTRIB                                                                      "columns"
#define TMX_FIRST_G_ID_ATTRIB                                                                   "firstgid"
#define TMX_TILE_WIDTH_ATTRIB                                                                   "tilewidth"
#define TMX_TILE_COUNT_ATTRIB                                                                   "tilecount"
#define TMX_TILE_HEIGHT_ATTRIB                                                                  "tileheight"

using namespace tinyxml2;

static std::vector<int> KMP_precomputed(const std::string& pattern){
    std::vector<int> pi;
    pi.push_back(-1);

    int k = -1;
    for (int q = 1; q < pattern.length(); ++q)
    {
        while (k > -1 && pattern[k + 1] != pattern[q])
            k = pi[k];
        if (pattern[k + 1] == pattern[q])
            k += 1;
        pi[q] = k;
    }

    return pi;
}

static std::vector<int> KMP_matcher(const std::string& text, const std::string& pattern){
    std::vector<int> result;
    std::vector<int> pi = KMP_precomputed(pattern);
    int q = -1;

    for (int i = 0; i < text.length(); ++i)
    {
        while (q > -1 && pattern[q + 1] != text[i])
            q = pi[q];
        if (pattern[q + 1] == text[i])
            q = q + 1;

        if (q == pattern.length() - 1)
        {
            result.push_back(i - pattern.length() + 1);
            q = pi[q];
        }
    }

    return result;
}

std::vector<int> string_split(const std::string &text, const std::string &separator)
{
    std::vector<int> shifts = KMP_matcher(text, separator);
    std::vector<int> result;
    int i = 0;
    for (auto j: shifts)
    {
        result.emplace_back(atoi(text.substr(i, j - i).c_str()));
        i = j + separator.length();
    }
    result.emplace_back(atoi(text.substr(i).c_str()));

    return result;
}

static std::vector<tmx::TileSet> load_tile_sets(const XMLDocument& tmx){
    const char *source, *name;
    XMLDocument tsx;
    std::vector<tmx::TileSet> result;
    int first_id, tile_width,
        tile_height, columns, tile_count;

    auto tmx_root = tmx.RootElement();
    tmx_root->QueryIntAttribute(TMX_TILE_WIDTH_ATTRIB, &tile_width);
    tmx_root->QueryIntAttribute(TMX_TILE_HEIGHT_ATTRIB, &tile_height);

    auto tile_set = tmx_root->FirstChildElement(TMX_TILE_SET_TAG);
    while (tile_set != nullptr){
        tile_set->QueryStringAttribute("source", &source);
        tile_set->QueryIntAttribute(TMX_FIRST_G_ID_ATTRIB, &first_id);

        tsx.LoadFile(std::string(_AZOR_TMX_TILE_SET_ROOT_DIR_).append(source).c_str());

        tsx.RootElement()->QueryIntAttribute(TMX_TILE_COUNT_ATTRIB, &tile_count);
        tsx.RootElement()->QueryIntAttribute(TMX_COLUMNS_ATTRIB, &columns);
        tsx.RootElement()->QueryStringAttribute(TMX_NAME_ATTRIB, &name);
        int rows = tile_count / columns;

        tmx::TileSet set(first_id, res::get_texture(name));
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                set.tiles.emplace_back(Rectangle(j * tile_width, i * tile_height, tile_width, tile_height));
            }
        }
        result.emplace_back(set);

        tile_set = tile_set->NextSiblingElement(TMX_TILE_SET_TAG);
    }

    return result;
}

static std::vector<std::vector<int>> load_layers(const XMLDocument& tmx){
    std::vector<std::vector<int>> result;

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
        result.emplace_back(string_split(real_data, ","));
        layer = layer->NextSiblingElement(TMX_LAYER_TAG);
    }

    return result;
}

tmx::Map* tmx::parse(const char *path)
{


    XMLDocument tmx;
    tmx.LoadFile(std::string(_AZOR_TMX_MAP_ROOT_DIR_).append(path).c_str());

    auto map = new Map();
    map->sets = load_tile_sets(tmx);
    map->layers = load_layers(tmx);

    tmx.RootElement()->QueryIntAttribute(TMX_WIDTH_ATTRIB, &map->width);
    tmx.RootElement()->QueryIntAttribute(TMX_HEIGHT_ATTRIB, &map->height);
    tmx.RootElement()->QueryIntAttribute(TMX_TILE_WIDTH_ATTRIB, &map->tile_width);
    tmx.RootElement()->QueryIntAttribute(TMX_TILE_HEIGHT_ATTRIB, &map->tile_height);

    return map;
}
