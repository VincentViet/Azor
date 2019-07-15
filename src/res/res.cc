//
// Created by vice on 14/07/2019.
//

#include "res.h"
#include <glad/glad.h>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

namespace res
{
enum class ShaderType
{
    PROGRAM,
    VERTEX_SHADER,
    FRAGMENT_SHADER
};

static std::map<const char *, Texture> textures;

}

static bool check_error(uint32_t id, res::ShaderType type)
{
    int success;
    char infoLog[1024];
    if (type != res::ShaderType::PROGRAM)
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
    if (!check_error(id, res::ShaderType::VERTEX_SHADER))
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
    if (!check_error(id, res::ShaderType::FRAGMENT_SHADER))
        return id;

    return 0;
}

Shader *res::create_shader_program(const char *vs_path, const char *fs_path)
{
    uint32_t id = 0, vs = 0, fs = 0;
    Shader shader(0);
    if (vs_path)
        vs = create_vs(vs_path);
    if (fs_path)
        fs = create_fs(fs_path);

    if (vs && fs)
    {
        id = glCreateProgram();
        glAttachShader(id, vs);
        glAttachShader(id, fs);
        glLinkProgram(id);

        glDeleteShader(vs);
        glDeleteShader(fs);

        if (!check_error(id, res::ShaderType::PROGRAM))
            return new Shader(id);
    }

    return nullptr;
}

void res::load_texture_from_file(const char *path, const char *name)
{
    if (!res::textures.count(name))
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
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            if (nrChannels == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            else if (nrChannels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);

            Texture texture(id, width, height);
            res::textures.insert(std::pair<const char *, Texture>(name, texture));
        } else
        {
            fprintf(stderr, "[RES_IMAGE_ERROR]: no such file %s", path);
        }
        stbi_image_free(data);
    }
}

Texture *res::get_texture(const char *name)
{
    return &res::textures.at(name);
}

