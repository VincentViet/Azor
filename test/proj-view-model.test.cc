//
// Created by vice on 14/07/2019.
//

#include <catch2/catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

TEST_CASE("project view model", "[proj-view-model]"){
    glm::mat4 projection = glm::ortho(0.0f, (float)1280, (float)800, 0.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0, 0, 0));
    model = glm::scale(model, glm::vec3(1097, 1087, 0));

    glm::vec4 v(0.5f, 0.5f, 0.0f, 1.0f);

    v = projection * view * model * v;
    printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);
}

