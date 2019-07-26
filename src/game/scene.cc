//
// Created by vice on 19/07/2019.
//

#include "scene.h"
#include <map>
#include <config.h>
#include <renderer/SpriteBatch.h>
#include <glm/gtc/type_ptr.hpp>
#include <window/window.h>
#include <game/object/Hawkeye.h>


static std::map<std::string, Scene*> scenes;
static Scene* current_scene = nullptr;

void scene::startUp(tinyxml2::XMLElement *scenes_node)
{
    const char* name;
    const char* firstScene;

    if (scenes_node){
        auto scene = scenes_node->FirstChildElement(_AZOR_CONFIG_SCENE_TAG_);
        while (scene){
            scene->QueryStringAttribute(_AZOR_CONFIG_SCENES_NAME_ATTRIB_, &name);
            scenes.insert(std::pair<std::string, Scene*>(name, new Scene(scene)));

            scene = scene->NextSiblingElement(_AZOR_CONFIG_SCENE_TAG_);
        }

        scenes_node->QueryStringAttribute(_AZOR_CONFIG_SCENES_FIRST_SCENE_ATTRIB, &firstScene);
        current_scene = scenes.at(firstScene);
    }

    auto hawkeye = new Hawkeye(current_scene);
    current_scene->addEntity(hawkeye);
}

void scene::update()
{
    if (current_scene)
        current_scene->update();
}

void scene::draw(SpriteBatch* batch)
{
    if (current_scene)
    {
        batch->begin();

        current_scene->draw(batch);

        batch->end();
    }
}
void scene::changeScene(const char *name)
{
    current_scene = scenes.at(name);
}

void scene::shutdown()
{
    for (const auto& scene: scenes)
    {
        delete scene.second;
    }
    scenes.clear();
}
Scene::Scene(tinyxml2::XMLElement *scene)
{
    const char* name;
    int width, height;

    auto camera = scene->FirstChildElement(_AZOR_CONFIG_SCENES_CAMERA_TAG_);
    auto map = scene->FirstChildElement(_AZOR_CONFIG_SCENES_MAP_TAG_);
    auto shader = scene->FirstChildElement(_AZOR_CONFIG_SCENES_SHADER_TAG_);

    camera->QueryIntAttribute(_AZOR_CONFIG_SCENES_WIDTH_ATTRIB, &width);
    camera->QueryIntAttribute(_AZOR_CONFIG_SCENES_HEIGHT_ATTRIB, &height);
    map->QueryStringAttribute(_AZOR_CONFIG_SCENES_NAME_ATTRIB_, &name);

    m_camera = new Camera({0, 0}, width, height);

    m_map = resources::getMap(name);
    m_map->setScene(this);
    m_map->load();

    shader->QueryStringAttribute(_AZOR_CONFIG_SCENES_NAME_ATTRIB_, &name);
    m_shader = resources::getShader(name);
}
Scene::~Scene()
{
    delete m_camera;
}
void Scene::update()
{
    static glm::vec2 v(0);
    static float speed = 100.0f;

    // camera
    float delta_time = window::getDeltaTime();
    if (window::isKeyDown(window::Keys::UP))
        v -= glm::vec2(0, speed * delta_time);
    if (window::isKeyDown(window::Keys::DOWN))
        v += glm::vec2(0, speed * delta_time);
    if (window::isKeyDown(window::Keys::LEFT))
        v -= glm::vec2(speed * delta_time, 0);
    if (window::isKeyDown(window::Keys::RIGHT))
        v += glm::vec2(speed * delta_time, 0);

    m_camera->setPosition(v);
    m_shader->use();
    m_shader->set_matrix("projection", glm::value_ptr(m_camera->getProjection()));

    //object layer
    auto bound = m_camera->getBound();
    auto layer = m_map->getObjectLayer(0);
    auto objects = layer->retrieve(bound);
    for (auto& object: objects)
    {
        object->update();
    }

    for (auto& object: m_objects)
    {
        if (intersect(object->getBound(), bound)){
            object->setActive(true);
            object->update();
        }
        else object->setActive(false);
    }
}
void Scene::draw(SpriteBatch *batch)
{
    auto layer = m_map->getTileLayer(0);
    auto tiles = layer->retrieve(m_camera->getBound());

    for (auto& tile: tiles)
        if (tile.isValid()){
            batch->draw(&tile);
        }

    for (auto& object: m_objects)
    {
        if (object->isActive())
            batch->draw(object->getSprite());
    }
}
Camera *Scene::getCamera()
{
    return m_camera;
}
void Scene::addEntity(Entity *entity)
{
    m_objects.push_back(entity);
}

Scene* scene::getCurrentScene()
{
    return current_scene;
}
