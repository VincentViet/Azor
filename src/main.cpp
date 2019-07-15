#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <azor-conf.h>
#include <res/res.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <render/sprite-batch.h>

void error_callback(int error, const char *description)
{
    (void) error;
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scan_code, int action, int mods)
{
    (void) scan_code;
    (void) mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

static void centerWindow(GLFWwindow *window, GLFWmonitor *monitor)
{
    if (!monitor)
        return;

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    if (!mode)
        return;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    glfwSetWindowPos(window,
                     monitorX + (mode->width - windowWidth) / 2,
                     monitorY + (mode->height - windowHeight) / 2);
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(_AZOR_DEFAULT_WINDOW_WIDTH_,
                              _AZOR_DEFAULT_WINDOW_HEIGHT_,
                              _AZOR_DEFAULT_WINDOW_TITLE_,
                              nullptr,
                              nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    centerWindow(window, glfwGetPrimaryMonitor());

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, _AZOR_DEFAULT_WINDOW_WIDTH_, _AZOR_DEFAULT_WINDOW_HEIGHT_);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    res::load_texture_from_file("../res/fbs.png", "fbs");

    Shader* default_shader = res::create_shader_program(_AZOR_DEFAULT_VERTEX_SHADER_, _AZOR_DEFAULT_FRAGMENT_SHADER_);
    if (!default_shader)
    {
        glfwTerminate();
        return -1;
    }

    glm::mat4 projection = glm::ortho(
        (float)_AZOR_DEFAULT_WINDOW_WIDTH_ / -2,
        (float)_AZOR_DEFAULT_WINDOW_WIDTH_ / 2,
        (float)_AZOR_DEFAULT_WINDOW_WIDTH_ / -2,
        (float)_AZOR_DEFAULT_WINDOW_HEIGHT_ / 2,
        -10.0f,
        10.0f);
    glm::mat4 view = glm::mat4(1.0);

    default_shader->use();
    default_shader->set_matrix("projection", glm::value_ptr(projection));
    default_shader->set_matrix("view", glm::value_ptr(view));

    SpriteBatch sprite_batch;
    Sprite sprite("fbs", glm::vec2(640, 400));
    Sprite sprite1("fbs", glm::vec2(100, 0));
    Sprite sprite2("fbs", glm::vec2(-200, 0));
    Sprite sprite3("fbs", glm::vec2(0, 100));
    Sprite sprite4("fbs", glm::vec2(0, -200));
    Sprite sprite5("fbs", glm::vec2(-640, -400));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        sprite_batch.begin();

        sprite_batch.draw(sprite);
        sprite_batch.draw(sprite1);
        sprite_batch.draw(sprite2);
        sprite_batch.draw(sprite3);
        sprite_batch.draw(sprite4);
        sprite_batch.draw(sprite5);

        sprite_batch.end();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}