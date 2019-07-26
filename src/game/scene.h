//
// Created by vice on 19/07/2019.
//

#ifndef AZOR_SRC_SCENE_SCENE_H_
#define AZOR_SRC_SCENE_SCENE_H_

#include <tinyxml2.h>
#include "Camera.h"
#include <resources/resources.h>
#include <renderer/SpriteBatch.h>

class Scene
{
    Map* m_map{};
    Camera* m_camera{};
    Shader* m_shader{};

    std::vector<Entity*> m_objects;
 public:
    explicit            Scene(tinyxml2::XMLElement* scene);
                        ~Scene();
    void                update();
    void                draw(SpriteBatch* batch);

    void                addEntity(Entity* entity);
    Camera*             getCamera();
};

namespace scene{
    void            startUp(tinyxml2::XMLElement* scenes);
    void            update();
    void            draw(SpriteBatch* batch);
    Scene*          getCurrentScene();
    void            changeScene(const char* name);
    void            shutdown();
}


#endif //AZOR_SRC_SCENE_SCENE_H_
