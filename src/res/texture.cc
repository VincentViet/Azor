//
// Created by vice on 15/07/2019.
//

#include "texture.h"
#include <glad/glad.h>

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

