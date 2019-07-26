//
// Created by vice on 24/07/2019.
//

#include "renderer.h"
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <config.h>
#include <common/utils/string.h>


static SpriteBatch* batch;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

void renderer::startUp(tinyxml2::XMLElement* renderer)
{
    const char* viewport;
    int x, y, width, height;
    if (renderer){
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            glfwTerminate();
            exit(0);
        }

        renderer->QueryStringAttribute(_AZOR_CONFIG_RENDERER_VIEWPORT_ATTRIB_, &viewport);
        auto result = string::split(viewport, " ");
        x = atoi(result.at(0).c_str());
        y = atoi(result.at(1).c_str());
        width = atoi(result.at(2).c_str());
        height = atoi(result.at(3).c_str());

        glViewport(x, y, width, height);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        batch = new SpriteBatch;
    }
}

void renderer::update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

SpriteBatch* renderer::getSpriteBatch()
{
    return batch;
}

void renderer::shutdown()
{
    delete batch;
    batch = nullptr;
}