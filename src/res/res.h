//
// Created by vice on 14/07/2019.
//

#ifndef AZOR_RES_H_
#define AZOR_RES_H_

#include <cstdint>
#include "shader.h"
#include "texture.h"

namespace res{


    Shader* create_shader_program(const char* vs_path, const char* fs_path);
    void load_texture_from_file(const char* path, const char* name);
    Texture* get_texture(const char* name);
}

#endif //AZOR_RES_H_
