//
// Created by vice on 24/07/2019.
//

#include "config.h"
#include <logging.h>
#include <tinyxml2.h>
#include <game/scene.h>
#include <window/window.h>
#include <physics/physics.h>
#include <renderer/renderer.h>
#include <resources/resources.h>
#include <debug/dbg.h>

#include "Application.h"
namespace xml = tinyxml2;

void Application::run()
{
    while (!window::isClosed())
    {
        scene::update();
        renderer::update();
        debug::update();
        physics::update();
        scene::draw(renderer::getSpriteBatch());
        physics::draw();
        debug::draw();
        window::update();
    }
}

Application::Application()
{
    xml::XMLDocument config;
    config.LoadFile(_AZOR_CONFIG_FILE_);
    auto root = config.RootElement();


    //start up
    logging::startUp(root->FirstChildElement(_AZOR_CONFIG_LOGGING_TAG_));
    window::startUp(root->FirstChildElement(_AZOR_CONFIG_WINDOW_TAG_));
    renderer::startUp(root->FirstChildElement(_AZOR_CONFIG_RENDERER_TAG_));
    debug::startUp();
    physics::startUp(root->FirstChildElement(_AZOR_CONFIG_PHYSICS_WORLD_TAG_));
    resources::startUp(root->FirstChildElement(_AZOR_CONFIG_RESOURCES_TAG_));
    scene::startUp(root->FirstChildElement(_AZOR_CONFIG_SCENES_TAG_));
}
Application::~Application()
{
    scene::shutdown();
    resources::shutdown();
    physics::shutdown();
    debug::shutdown();
    renderer::shutdown();
    window::shutdown();
}
