//
// Created by vice on 24/07/2019.
//

#include "window.h"
#include <config.h>
#include <logging.h>
#include <cstdlib>
#include <GLFW/glfw3.h>


static GLFWwindow* m_window;
static int width;
static int height;

static double last_time = 0;
static double delta_time = 0;

static void key_callback(GLFWwindow *window, int key, int scan_code, int action, int mods)
{
    (void) scan_code;
    (void) mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void error_callback(int error, const char *description)
{
    (void) error;
    fprintf(stderr, "Error: %s\n", description);
}

extern void framebuffer_size_callback(GLFWwindow *window, int width, int height);

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

void window::startUp(tinyxml2::XMLElement *window_node)
{
    bool center;
    const char *title;

    if (window_node)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window_node->QueryIntAttribute(_AZOR_CONFIG_WINDOW_WIDTH_ATTRIB_, &width);
        window_node->QueryIntAttribute(_AZOR_CONFIG_WINDOW_HEIGHT_ATTRIB_, &height);
        window_node->QueryStringAttribute(_AZOR_CONFIG_WINDOW_TITLE_ATTRIB_, &title);
        window_node->QueryBoolAttribute(_AZOR_CONFIG_WINDOW_CENTER_SCREEN_ATTRIB_, &center);

        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!m_window)
        {
            LOG_CRITICAL("{0}:{1}:{2}: CAN'T CREATE GLFW WINDOW", __FILE__, __LINE__, __FUNCTION__);
            glfwTerminate();
            exit(0);
        }

        centerWindow(m_window, glfwGetPrimaryMonitor());

        glfwMakeContextCurrent(m_window);
        glfwSetErrorCallback(error_callback);
        glfwSetKeyCallback(m_window, key_callback);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    }
}

void window::shutdown()
{
    glfwTerminate();
}
bool window::isClosed()
{
    return glfwWindowShouldClose(m_window);
}
void window::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();

    double current_time = glfwGetTime();
    delta_time = current_time - last_time;
    last_time = current_time;
}

int window::getWidth()
{
    return width;
}

int window::getHeight()
{
    return height;
}

double window::getDeltaTime()
{ return delta_time;}

bool window::isKeyDown(window::Keys k)
{
    return glfwGetKey(m_window, (int)k) == GLFW_PRESS;
}

bool window::isKeyUp(window::Keys k)
{
    return glfwGetKey(m_window, (int)k) == GLFW_RELEASE;
}

GLFWwindow* window::getWindow()
{
    return m_window;
}