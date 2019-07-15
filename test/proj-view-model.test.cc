//
// Created by vice on 14/07/2019.
//

#include <catch2/catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

TEST_CASE("project view model", "[proj-view-model]"){
    glm::mat4 projection = glm::ortho(0.0f, (float)1280, (float)800, 0.0f, -10.0f, 10.0f);
    glm::mat4 view = glm::mat4(1.0);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(640, 400, 0));
    model = glm::scale(model, glm::vec3(1087 / 2.0f, 1097 / 2.0f, 0));

    glm::vec4 v1(0.5f, 0.5f, 0, 1);
    glm::vec4 v2(0.5f, -0.5f, 0, 1);
    glm::vec4 v3(-0.5f, 0.5f, 0, 1);
    glm::vec4 v4(-0.5f, -0.5f, 0, 1);

    v1 = /*projection * view **/ model * v1;
    printf("%f %f %f %f\n", v1.x, v1.y, v1.z, v1.w);

    v2 = /*projection * view **/ model * v2;
    printf("%f %f %f %f\n", v2.x, v2.y, v2.z, v2.w);

    v3 = /*projection * view **/ model * v3;
    printf("%f %f %f %f\n", v3.x, v3.y, v3.z, v3.w);

    v4 = /*projection * view **/ model * v4;
    printf("%f %f %f %f\n", v4.x, v4.y, v4.z, v4.w);
}

