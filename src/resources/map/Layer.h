//
// Created by vice on 26/07/2019.
//

#ifndef AZOR_SRC_RESOURCES_MAP_LAYER_H_
#define AZOR_SRC_RESOURCES_MAP_LAYER_H_

#include <vector>
#include <common/AABB.h>

template <class T>
class Layer
{
 private:
    std::vector<T> m_data;
    std::vector<T> m_potential;

 public:
    Layer() = default;
    ~Layer();

    void insert(T& data);
    std::vector<T>& retrieve(const AABB& aabb);
};

#endif //AZOR_SRC_RESOURCES_MAP_LAYER_H_
