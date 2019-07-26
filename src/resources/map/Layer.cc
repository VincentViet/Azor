//
// Created by vice on 26/07/2019.
//

#include "Layer.h"
#include "Tile.h"
#include <game/object/Entity.h>

template<>
void Layer<Tile>::insert(Tile &data)
{
    m_data.emplace_back(data);
}

template<>
std::vector<Tile> &Layer<Tile>::retrieve(const AABB &aabb)
{
    m_potential.clear();
    for (auto& data: m_data)
    {
        if (intersect(data.getBound(), aabb))
            m_potential.emplace_back(data);
    }
    return m_potential;
}
template<>
Layer<Tile>::~Layer()
{}

template<>
Layer<Entity*>::~Layer()
{
    for (auto& entity: m_data)
    {
        delete entity;
    }
}

template<>
void Layer<Entity*>::insert(Entity* &data)
{
    m_data.emplace_back(data);
}

template<>
std::vector<Entity*> &Layer<Entity*>::retrieve(const AABB &aabb)
{
    m_potential.clear();
    for (auto& data: m_data)
    {
        if (intersect(data->getBound(), aabb))
        {
//            data->setActive(true);
            m_potential.emplace_back(data);
        }
//        else data->setActive(false);
    }
    return m_potential;
}


