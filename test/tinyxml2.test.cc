//
// Created by vice on 17/07/2019.
//

#include <catch2/catch.hpp>
#include <tmxparser/tmxparser.h>

TEST_CASE("Tiny xml", "[xml]"){
    tmx::parse("scene1.tmx");
}