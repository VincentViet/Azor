//
// Created by vice on 17/07/2019.
//

#ifndef AZOR_COMMON_REC_H_
#define AZOR_COMMON_REC_H_

#include <glm/vec2.hpp>
#include <Box2D/Collision/b2Collision.h>

struct AABB
{
    glm::vec2 min{};
    glm::vec2 max{};
    AABB()
        :min(0), max(0)
    {}

    AABB(const b2AABB& aabb)
        :   min(aabb.lowerBound.x, aabb.lowerBound.y),
            max(aabb.upperBound.x, aabb.upperBound.y)
    {}

    AABB(float x, float y, float w, float h)
        :min(x, y), max(x + w, y + h)
    {}

    AABB(const glm::vec2& p, float w, float h)
        : min(p), max(p.x + w, p.y + h)
    {}

    AABB(float x, float y, const glm::vec2& size)
        : min(x, y), max(min + size)
    {}

    AABB(const glm::vec2& min, const glm::vec2& size)
        : min(min), max(min + size)
    {}

    glm::vec2 getSize() const{
        return max - min;
    }

    glm::vec2 getPos() const {
        return min + (max - min) * 0.5f;
    }

    glm::vec2 setPos(const glm::vec2& pos){
        auto size = (max - min);
        min = pos;
        max = pos + size;
    }
};

inline bool intersect(const AABB& a, const AABB& b){
    return !(b.max.x < a.min.x ||
        b.max.y < a.min.y ||
        b.min.x > a.max.x ||
        b.min.y > a.max.y);

}

#endif //AZOR_SRC_COMMON_REC_H_
