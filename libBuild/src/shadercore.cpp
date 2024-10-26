#include "shadercore.hpp"

#include <lc.hpp>
#include <fios.hpp>

namespace gfx
{
    std::string GLTypeToString(GLenum type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return "GL_FLOAT";
        case GL_FLOAT_VEC2:
            return "GL_FLOAT_VEC2";
        case GL_FLOAT_VEC3:
            return "GL_FLOAT_VEC3";
        case GL_FLOAT_VEC4:
            return "GL_FLOAT_VEC4";
        case GL_INT:
            return "GL_INT";
        case GL_INT_VEC2:
            return "GL_INT_VEC2";
        case GL_INT_VEC3:
            return "GL_INT_VEC3";
        case GL_INT_VEC4:
            return "GL_INT_VEC4";
        case GL_UNSIGNED_INT:
            return "GL_UNSIGNED_INT";
        case GL_UNSIGNED_INT_VEC2:
            return "GL_UNSIGNED_INT_VEC2";
        case GL_UNSIGNED_INT_VEC3:
            return "GL_UNSIGNED_INT_VEC3";
        case GL_UNSIGNED_INT_VEC4:
            return "GL_UNSIGNED_INT_VEC4";
        case GL_BOOL:
            return "GL_BOOL";
        case GL_BOOL_VEC2:
            return "GL_BOOL_VEC2";
        case GL_BOOL_VEC3:
            return "GL_BOOL_VEC3";
        case GL_BOOL_VEC4:
            return "GL_BOOL_VEC4";
        case GL_FLOAT_MAT2:
            return "GL_FLOAT_MAT2";
        case GL_FLOAT_MAT3:
            return "GL_FLOAT_MAT3";
        case GL_FLOAT_MAT4:
            return "GL_FLOAT_MAT4";
        case GL_SAMPLER_1D:
            return "GL_SAMPLER_1D";
        case GL_SAMPLER_2D:
            return "GL_SAMPLER_2D";
        case GL_SAMPLER_3D:
            return "GL_SAMPLER_3D";
        case GL_SAMPLER_CUBE:
            return "GL_SAMPLER_CUBE";
        case GL_SAMPLER_1D_SHADOW:
            return "GL_SAMPLER_1D_SHADOW";
        case GL_SAMPLER_2D_SHADOW:
            return "GL_SAMPLER_2D_SHADOW";
        case GL_SAMPLER_1D_ARRAY:
            return "GL_SAMPLER_1D_ARRAY";
        case GL_SAMPLER_2D_ARRAY:
            return "GL_SAMPLER_2D_ARRAY";
        case GL_SAMPLER_1D_ARRAY_SHADOW:
            return "GL_SAMPLER_1D_ARRAY_SHADOW";
        case GL_SAMPLER_2D_ARRAY_SHADOW:
            return "GL_SAMPLER_2D_ARRAY_SHADOW";
        case GL_SAMPLER_2D_MULTISAMPLE:
            return "GL_SAMPLER_2D_MULTISAMPLE";
        case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
            return "GL_SAMPLER_2D_MULTISAMPLE_ARRAY";
        case GL_SAMPLER_CUBE_SHADOW:
            return "GL_SAMPLER_CUBE_SHADOW";
        case GL_SAMPLER_BUFFER:
            return "GL_SAMPLER_BUFFER";
        case GL_SAMPLER_2D_RECT:
            return "GL_SAMPLER_2D_RECT";
        case GL_SAMPLER_2D_RECT_SHADOW: 
            return "GL_SAMPLER_2D_RECT_SHADOW";
        case GL_INT_SAMPLER_1D:
            return "GL_INT_SAMPLER_1D";
        case GL_INT_SAMPLER_2D:
            return "GL_INT_SAMPLER_2D";
        case GL_INT_SAMPLER_3D:
            return "GL_INT_SAMPLER_3D";
        case GL_INT_SAMPLER_CUBE:
            return "GL_INT_SAMPLER_CUBE";
        case GL_INT_SAMPLER_1D_ARRAY:   
            return "GL_INT_SAMPLER_1D_ARRAY";
        case GL_INT_SAMPLER_2D_ARRAY:
            return "GL_INT_SAMPLER_2D_ARRAY";
        case GL_INT_SAMPLER_2D_MULTISAMPLE:
            return "GL_INT_SAMPLER_2D_MULTISAMPLE";
        case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
            return "GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
        case GL_INT_SAMPLER_BUFFER:
            return "GL_INT_SAMPLER_BUFFER";
        case GL_INT_SAMPLER_2D_RECT:
            return "GL_INT_SAMPLER_2D_RECT";
        case GL_UNSIGNED_INT_SAMPLER_1D:    
            return "GL_UNSIGNED_INT_SAMPLER_1D";
        case GL_UNSIGNED_INT_SAMPLER_2D:
            return "GL_UNSIGNED_INT_SAMPLER_2D";
        case GL_UNSIGNED_INT_SAMPLER_3D:
            return "GL_UNSIGNED_INT_SAMPLER_3D";
        case GL_UNSIGNED_INT_SAMPLER_CUBE:
            return "GL_UNSIGNED_INT_SAMPLER_CUBE";
        case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
            return "GL_UNSIGNED_INT_SAMPLER_1D_ARRAY";
        case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:  
            return "GL_UNSIGNED_INT_SAMPLER_2D_ARRAY";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
            return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
            return "GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY";
        case GL_UNSIGNED_INT_SAMPLER_BUFFER:
            return "GL_UNSIGNED_INT_SAMPLER_BUFFER";
        case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
            return "GL_UNSIGNED_INT_SAMPLER_2D_RECT";
        case GL_IMAGE_1D:
            return "GL_IMAGE_1D";
        case GL_IMAGE_2D:
            return "GL_IMAGE_2D";
        case GL_IMAGE_3D:
            return "GL_IMAGE_3D";
        case GL_IMAGE_2D_RECT:  
            return "GL_IMAGE_2D_RECT";
        case GL_IMAGE_CUBE:
            return "GL_IMAGE_CUBE";
        case GL_IMAGE_BUFFER:
            return "GL_IMAGE_BUFFER";
        case GL_IMAGE_1D_ARRAY:
            return "GL_IMAGE_1D_ARRAY";
        case GL_IMAGE_2D_ARRAY: 
            return "GL_IMAGE_2D_ARRAY";
        case GL_IMAGE_2D_MULTISAMPLE:   
            return "GL_IMAGE_2D_MULTISAMPLE";
        case GL_IMAGE_2D_MULTISAMPLE_ARRAY:
            return "GL_IMAGE_2D_MULTISAMPLE_ARRAY";
        case GL_INT_IMAGE_1D:
            return "GL_INT_IMAGE_1D";
        case GL_INT_IMAGE_2D:
            return "GL_INT_IMAGE_2D";
        case GL_INT_IMAGE_3D:
            return "GL_INT_IMAGE_3D";
        case GL_INT_IMAGE_2D_RECT:
            return "GL_INT_IMAGE_2D_RECT";
        case GL_INT_IMAGE_CUBE:
            return "GL_INT_IMAGE_CUBE";
        case GL_INT_IMAGE_BUFFER:
            return "GL_INT_IMAGE_BUFFER";
        case GL_INT_IMAGE_1D_ARRAY:
            return "GL_INT_IMAGE_1D_ARRAY";
        case GL_INT_IMAGE_2D_ARRAY:
            return "GL_INT_IMAGE_2D_ARRAY";
        case GL_INT_IMAGE_2D_MULTISAMPLE:
            return "GL_INT_IMAGE_2D_MULTISAMPLE";
        case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
            return "GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY";
        case GL_UNSIGNED_INT_IMAGE_1D:
            return "GL_UNSIGNED_INT_IMAGE_1D";
        case GL_UNSIGNED_INT_IMAGE_2D:
            return "GL_UNSIGNED_INT_IMAGE_2D";
        case GL_UNSIGNED_INT_IMAGE_3D:
            return "GL_UNSIGNED_INT_IMAGE_3D";
        case GL_UNSIGNED_INT_IMAGE_2D_RECT:
            return "GL_UNSIGNED_INT_IMAGE_2D_RECT";
        case GL_UNSIGNED_INT_IMAGE_CUBE:
            return "GL_UNSIGNED_INT_IMAGE_CUBE";
        case GL_UNSIGNED_INT_IMAGE_BUFFER:
            return "GL_UNSIGNED_INT_IMAGE_BUFFER";
        case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:
            return "GL_UNSIGNED_INT_IMAGE_1D_ARRAY";
        case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:
            return "GL_UNSIGNED_INT_IMAGE_2D_ARRAY";
        case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
            return "GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE";
        case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
            return "GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY";
        case GL_UNSIGNED_INT_ATOMIC_COUNTER:
            return "GL_UNSIGNED_INT_ATOMIC_COUNTER";
        default:
            return "UNKNOWN";
        }
    }

    std::vector<Attribute> GetActiveAttributes(unsigned int program)
    {
        int count;
        glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
        std::vector<Attribute> attributes;
        attributes.reserve(count);
        for (int i = 0; i < count; i++)
        {
            char name[128];
            int size;
            GLenum type;
            glGetActiveAttrib(program, i, 128, nullptr, &size, &type, name);
            attributes.emplace_back(Attribute{name, type, size});
        }
        return attributes;
    }

    std::vector<Uniform> GetActiveUniforms(unsigned int program)
    {
        int count;
        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
        std::vector<Uniform> uniforms;
        uniforms.reserve(count);
        for (int i = 0; i < count; i++)
        {
            char name[128];
            int size;
            GLenum type;
            glGetActiveUniform(program, i, 128, nullptr, &size, &type, name);
            uniforms.emplace_back(Uniform{name, type, size});
        }
        return uniforms;
    }

    void PrintAllAttrUnif(unsigned int program)
    {
        auto attributes = GetActiveAttributes(program);
        lc::Log<GL>("DEBUG", "Active Attributes: {}", attributes.size());
        for (auto& attr : attributes)
            lc::Log<GL>("DEBUG", "Attribute: {}, Size: {}, Type: {}", attr.name, attr.size, GLTypeToString(attr.type));

        auto uniforms = GetActiveUniforms(program);
        lc::Log<GL>("DEBUG", "Active Uniforms: {}", uniforms.size());
        for (auto& uniform : uniforms)
            lc::Log<GL>("DEBUG", "Uniform: {}, Size: {}, Type: {}", uniform.name, uniform.size, GLTypeToString(uniform.type));
    }

    bool isShaderCompiled(unsigned int shader)
    {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            lc::Log<GL>("ERROR", "Shader compilation failed: {}", infoLog);
            return false;
        }
        return true;
    }

    bool isProgramLinked(unsigned int program)
    {
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            lc::Log<GL>("ERROR", "Shader program linking failed: {}", infoLog);
            return false;
        }
        return true;
    }

    bool isProgramValid(unsigned int program)
    {
        glValidateProgram(program);
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            lc::Log<GL>("ERROR", "Shader program validation failed: {}", infoLog);
            return false;
        }
        return true;
    }

    unsigned int compileShader(const char* source, GLenum type)
    {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        isShaderCompiled(shader);
        free((void*)source);
        return shader;
    }

    unsigned int createShaderProgram(std::vector<unsigned int>& shaders)
    {
        unsigned int program = glCreateProgram();
        for (auto shader : shaders)
            glAttachShader(program, shader);
        glLinkProgram(program);
        isProgramLinked(program);
        for (auto shader : shaders)
            glDeleteShader(shader);
        return program;
    }

    void loadShader(unsigned int& program, std::vector<std::pair<std::string, GLenum>>& paths)
    {
        size_t size = 0;
        std::vector<unsigned int> newShaders;
        newShaders.reserve(paths.size());
        for (auto& path : paths)
        {
            size = 0;
            char* source = (char*)eutil::fios::ReadDataFromFile(path.first.c_str(), size, true);
            if (source == nullptr)
            {
                lc::Log<GL>("ERROR", "Failed to read shader source: {}", path.first);
                return;
            }
            unsigned int shader = compileShader(source, path.second);
            if(shader != 0)
                newShaders.emplace_back(shader);
        }

        unsigned int newProgram = createShaderProgram(newShaders);

        if (isProgramValid(newProgram))
        {
            glDeleteProgram(program);
            program = newProgram;
        }
        else
        {
            glDeleteProgram(newProgram);
            program = 0;
        }
    }
}