//
// Created by vice on 15/07/2019.
//

#ifndef AZOR_SRC_RES_SHADER_H_
#define AZOR_SRC_RES_SHADER_H_

#include <cstdint>

class Shader{
 private:
    uint32_t program;
 public:
    explicit Shader(uint32_t program):program(program){}
    ~Shader();

    void use();
    void set_bool(const char* name, bool value);
    void set_int(const char* name, int value);
    void set_float(const char* name, float value);
    void set_matrix(const char* name, float* matrix);
};

#endif //AZOR_SRC_RES_SHADER_H_
