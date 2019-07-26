//
// Created by vice on 20/07/2019.
//

#include <catch2/catch.hpp>
#include <common/AABB.h>

TEST_CASE("rect", "[common]"){
    AABB lr;
    lr.min = glm::vec2(0, 832);
    lr.max = lr.min + glm::vec2(32, 32);
    
    glm::vec2 result = lr.getPos();
    REQUIRE(result.x == 16);
    REQUIRE(result.y == 848);
}
