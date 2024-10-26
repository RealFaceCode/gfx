#pragma once

#include "defines.hpp"
#include <glad/glad.h>
#include <string>
#include <vector>

namespace gfx
{
    struct Uniform
    {
        std::string name;
        GLenum type;
        int size;
    };
    typedef Uniform Attribute;

    GFX_API std::string GLTypeToString(GLenum type);
    GFX_API std::vector<Attribute> GetActiveAttributes(unsigned int program);
    GFX_API std::vector<Uniform> GetActiveUniforms(unsigned int program);
    GFX_API void PrintAllAttrUnif(unsigned int program);
    GFX_API bool isShaderCompiled(unsigned int shader);
    GFX_API bool isProgramLinked(unsigned int program);
    GFX_API bool isProgramValid(unsigned int program);
    GFX_API unsigned int compileShader(const char* source, GLenum type);
    GFX_API unsigned int createShaderProgram(std::vector<unsigned int>& shaders);
    GFX_API void loadShader(unsigned int& program, std::vector<std::pair<std::string, GLenum>>& paths);
}