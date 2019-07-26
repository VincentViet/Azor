//
// Created by vice on 14/07/2019.
//

#include "SpriteBatch.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

void SpriteBatch::begin()
{
    batches.clear();
    textures.clear();
    for (uint32_t id: vao)
    {
        glDeleteVertexArrays(1, &id);
    }
    vao.clear();
}
void SpriteBatch::end()
{
    for (auto& pair: batches)
    {
        uint32_t vao_id, vbo_id;
        glGenVertexArrays(1, &vao_id);
        glGenBuffers(1, &vbo_id);
        vao.push_back(vao_id);

        glBindVertexArray(vao_id);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
        glBufferData(GL_ARRAY_BUFFER, pair.second.size() * sizeof(float), pair.second.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteBuffers(1, &vbo_id);
    }

    for (int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glBindVertexArray(vao[i]);
        glDrawArrays(GL_TRIANGLES, 0, batches.at(textures[i]).size() / 4);
    }
}
void SpriteBatch::draw(Sprite *sprite)
{
    Texture* texture = sprite->getTexture();
    glm::vec4* sprite_data = sprite->getData();
    for (uint32_t id: textures)
    {

        if (id == texture->id)
            goto execute;
    }
    textures.push_back(texture->id);
    batches.insert(std::pair<uint32_t, std::vector<float>>(texture->id, std::vector<float>()));


execute:
    auto& data = batches.at(texture->id);
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; ++j)
        {
            data.push_back(sprite_data[i][j]);
        }
    }
}

