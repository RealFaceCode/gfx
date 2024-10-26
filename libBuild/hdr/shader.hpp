#pragma once

#include "shadercore.hpp"
#include "defines.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>


namespace gfx
{
    struct GFX_API Shader
    {
    public:
        Shader();
        Shader(const std::vector<std::pair<std::string, GLenum>>& paths);
        Shader(const Shader& other);
        Shader(Shader&& other);
        Shader& operator=(Shader&& other);
        ~Shader();

        void build();
        bool inUse();
        void use();
        void unuse();

        void setUniform(const std::string& name, float value);
        void setUniform(const std::string& name, int value);
        void setUniform(const std::string& name, const glm::vec2& value);
        void setUniform(const std::string& name, const glm::vec3& value);
        void setUniform(const std::string& name, const glm::vec4& value);
        void setUniform(const std::string& name, const glm::mat2& value);
        void setUniform(const std::string& name, const glm::mat3& value);
        void setUniform(const std::string& name, const glm::mat4& value);
        void setUniform(const std::string& name, const glm::mat2x3& value);
        void setUniform(const std::string& name, const glm::mat2x4& value);
        void setUniform(const std::string& name, const glm::mat3x2& value);
        void setUniform(const std::string& name, const glm::mat3x4& value);
        void setUniform(const std::string& name, const glm::mat4x2& value);
        void setUniform(const std::string& name, const glm::mat4x3& value);
        void setUniform(const std::string& name, const std::vector<float>& value);
        void setUniform(const std::string& name, const std::vector<int>& value);
        void setUniform(const std::string& name, const std::vector<glm::vec2>& value);
        void setUniform(const std::string& name, const std::vector<glm::vec3>& value);
        void setUniform(const std::string& name, const std::vector<glm::vec4>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat2>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat3>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat4>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat2x3>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat2x4>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat3x2>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat3x4>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat4x2>& value);
        void setUniform(const std::string& name, const std::vector<glm::mat4x3>& value);

    private:
        unsigned int program;
        std::vector<std::pair<std::string, GLenum>> paths;
        std::vector<std::pair<Uniform, int>> uniforms;
    };
}