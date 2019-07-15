//
// Created by vice on 15/07/2019.
//

#include "shader.h"
#include <glad/glad.h>

Shader::~Shader()
{
    glDeleteProgram(this->program);
}
void Shader::set_bool(const char *name, bool value)
{
    glUniform1i(glGetUniformLocation(program, name), (int)value);
}
void Shader::set_int(const char *name, int value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
}
void Shader::set_float(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(program, name), value);
}
void Shader::set_matrix(const char *name, float *matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, matrix);
}
void Shader::use()
{
    glUseProgram(program);
}
