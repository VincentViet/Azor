////
//// Created by vice on 19/07/2019.
////
//
//#include <catch2/catch.hpp>
//#include <maps/Map.h>
////#include <camera/camera.h>
//
//TEST_CASE("quad tree", "[common]"){
//
//    AABB camera(glm::vec2(0, 0), glm::vec2(1280, 800));
//    Map maps;
//    maps.load("scene1.xml");
//
//    auto layer = maps.getLayer(0);
//    auto result = layer->retrieve(camera);
//
////    int i = 0;
////    for (auto& tile: result)
////    {
////        if (i % 40 || i == 0)
////            printf("%d ", tile.id_);
////        else
////            printf("\n%d ", tile.id_);
////        i++;
////    }
//    printf("%zu\n", result.size());
//}