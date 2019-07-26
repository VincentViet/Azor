//
// Created by vice on 14/07/2019.
//

#include "resources.h"
#include <glad/glad.h>
#include <cstdio>
#include <config.h>
#include <logging.h>
#include <cstring>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

enum class ShaderType
{
    PROGRAM,
    VERTEX_SHADER,
    FRAGMENT_SHADER
};

#define VERTEX_SHADER_TYPE "VERTEX"

static std::map<std::string, Texture*> textures;
static std::map<std::string, Shader*> programs;
static std::map<std::string, Map*> maps;


static bool check_error(uint32_t id, ShaderType type)
{
    int success;
    char infoLog[1024];
    if (type != ShaderType::PROGRAM)
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            fprintf(stderr, "[RES_SHADER_ERROR]: %s", infoLog);
        }
    } else
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, nullptr, infoLog);
            fprintf(stderr, "[RES_PROGRAM_ERROR]: %s", infoLog);
        }
    }

    return !success;
}

static std::string load_shader_source(const char *path)
{
    std::ifstream file;
    std::string source;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {

        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        source = stream.str();
    }
    catch (const std::ifstream::failure &e)
    {
        fprintf(stderr, "[RES_SHADER_FILE_ERROR]: %s", e.what());
    }

    return source;
}

static uint32_t create_vs(const char *vs)
{
    uint32_t id = glCreateShader(GL_VERTEX_SHADER);
    std::string source = load_shader_source(vs);
    const char *source_ptr = source.c_str();
    glShaderSource(id, 1, &source_ptr, nullptr);
    glCompileShader(id);
    if (!check_error(id, ShaderType::VERTEX_SHADER))
        return id;

    return 0;
}

static uint32_t create_fs(const char *fs)
{
    uint32_t id = glCreateShader(GL_FRAGMENT_SHADER);
    std::string source = load_shader_source(fs);
    const char *source_ptr = source.c_str();
    glShaderSource(id, 1, &source_ptr, nullptr);
    glCompileShader(id);
    if (!check_error(id, ShaderType::FRAGMENT_SHADER))
        return id;

    return 0;
}

static void loadShaderProgram(const std::string& vs_path, const std::string& fs_path, const char* name)
{
    uint32_t id = 0, vs = 0, fs = 0;
    vs = create_vs(std::string(_AZOR_SHADERS_DIR_).append(vs_path).c_str());
    fs = create_fs(std::string(_AZOR_SHADERS_DIR_).append(fs_path).c_str());

    if (vs && fs)
    {
        id = glCreateProgram();
        glAttachShader(id, vs);
        glAttachShader(id, fs);
        glLinkProgram(id);

        glDeleteShader(vs);
        glDeleteShader(fs);

        if (!check_error(id, ShaderType::PROGRAM))
            programs.insert(std::pair<std::string, Shader*>(name, new Shader(id)));
    }
}

static void loadTexture(const std::string& path, const char* name)
{
    if (!textures.count(name))
    {
        uint32_t id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(std::string(_AZOR_IMAGES_DIR_).append(path).c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            if (nrChannels == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            else if (nrChannels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);

            textures.insert(std::pair<std::string, Texture*>(name, new Texture(id, width, height)));
        } else
        {
            LOG_ERROR("{0}:{1}:{2}: no such file {3}", __FILE__, __LINE__, __FUNCTION__, path);
        }
        stbi_image_free(data);
    }
}

void resources::startUp(tinyxml2::XMLElement *resources)
{
    const char* path;
    const char* name;
    const char* type;
    if(resources){
        // load images
        auto images = resources->FirstChildElement(_AZOR_CONFIG_RESOURCES_IMAGES_TAG_);
        auto img = images->FirstChildElement(_AZOR_CONFIG_RESOURCES_IMG_TAG_);
        while (img){
            img->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_NAME_ATTRIB_, &name);
            img->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_SRC_ATTRIB_, &path);
            loadTexture(path, name);

            img = img->NextSiblingElement(_AZOR_CONFIG_RESOURCES_IMG_TAG_);
        }

        // shaders
        auto shader_programs = resources->FirstChildElement(_AZOR_CONFIG_RESOURCES_SHADER_PROGRAM_TAG_);
        auto program = shader_programs->FirstChildElement(_AZOR_CONFIG_RESOURCES_PROGRAM_TAG_);
        while (program){
            const char *vs_path = nullptr;
            const char *fs_path = nullptr;
            auto shader = program->FirstChildElement(_AZOR_CONFIG_RESOURCES_SHADER_TAG_);
            program->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_NAME_ATTRIB_, &name);
            while (shader){
                shader->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_TYPE_ATTRIB_, &type);
                if (!strcmp(type, VERTEX_SHADER_TYPE))
                    shader->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_SRC_ATTRIB_, &vs_path);
                else
                    shader->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_SRC_ATTRIB_, &fs_path);

                shader = shader->NextSiblingElement(_AZOR_CONFIG_RESOURCES_SHADER_TAG_);
            }
            loadShaderProgram(vs_path, fs_path, name);


            program = program->NextSiblingElement(_AZOR_CONFIG_RESOURCES_PROGRAM_TAG_);
        }

        // maps
        auto maps_node = resources->FirstChildElement(_AZOR_CONFIG_RESOURCES_MAPS_TAG_);
        auto map = maps_node->FirstChildElement(_AZOR_CONFIG_RESOURCES_MAP_TAG_);
        Map* m;
        while (map){
            map->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_NAME_ATTRIB_, &name);
            map->QueryStringAttribute(_AZOR_CONFIG_RESOURCES_SRC_ATTRIB_, &path);
            m = new Map(path);
            maps.insert(std::pair<std::string, Map*>(name, m));

            map = map->NextSiblingElement(_AZOR_CONFIG_RESOURCES_MAP_TAG_);
        }
    }
}

void resources::shutdown()
{
    for (const auto& program: programs)
    {
        delete program.second;
    }
    programs.clear();

    for (const auto& texture: textures)
    {
        delete texture.second;
    }
    textures.clear();
}

Texture * resources::getTexture(const char *name)
{
    return textures.at(name);
}

Map* resources::getMap(const char *name)
{
    return maps.at(name);
}

Shader* resources::getShader(const char *name)
{
    return programs.at(name);
}

