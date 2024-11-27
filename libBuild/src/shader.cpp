#include "shader.hpp"
#include <lc.hpp>


namespace gfx
{
    Shader::Shader::Shader()
    : program(0), paths() {}

    Shader::Shader(const std::vector<std::pair<std::string, GLenum>>& paths)
    : program(0), paths(paths) {}

    Shader::Shader(const Shader& other)
    : program(other.program), paths(other.paths)  {}

    Shader::Shader(Shader&& other)
    : program(other.program), paths(std::move(other.paths)) {}

    Shader& Shader::operator=(Shader&& other)
    {
        program = other.program;
        paths = std::move(other.paths);
        return *this;
    }

    Shader::~Shader()
    {
        if (program != 0)
            glDeleteProgram(program);
    }

    void Shader::build()
    {
        LoadShader(program, paths);
        auto uniform = GetActiveUniforms(program);
        uniforms.clear();
        uniforms.reserve(uniform.size());
        for (auto& u : uniform)
            uniforms.emplace_back(u, glGetUniformLocation(program, u.name.c_str()));
    }

    bool Shader::inUse()
    {
        GLint currentProgram = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
        return (currentProgram == program);
    }

    void Shader::use()
    {
        glUseProgram(program);
    }

    void Shader::unuse()
    {
        glUseProgram(0);
    }

    void Shader::setUniform(const std::string& name, float value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniform1f(it->second, value);
    }

    void Shader::setUniform(const std::string& name, int value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniform1i(it->second, value);
    }

    void Shader::setUniform(const std::string& name, const glm::vec2& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniform2fv(it->second, 1, &value[0]);
    }

    void Shader::setUniform(const std::string& name, const glm::vec3& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniform3fv(it->second, 1, &value[0]);
    }

    void Shader::setUniform(const std::string& name, const glm::vec4& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniform4fv(it->second, 1, &value[0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat2& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix2fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat3& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix3fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat4& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix4fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat2x3& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix2x3fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat2x4& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix2x4fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat3x2& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix3x2fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat3x4& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix3x4fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat4x2& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix4x2fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const glm::mat4x3& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniformMatrix4x3fv(it->second, 1, GL_FALSE, &value[0][0]);
    }

    void Shader::setUniform(const std::string& name, const std::vector<float>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniform1fv(it->second, value.size(), value.data());
    }

    void Shader::setUniform(const std::string& name, const std::vector<int>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
            glUniform1iv(it->second, value.size(), value.data());
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::vec2>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 2);
            for (auto& v : value)
            {
                data.emplace_back(v.x);
                data.emplace_back(v.y);
            }
            glUniform2fv(it->second, value.size(), data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::vec3>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 3);
            for (auto& v : value)
            {
                data.emplace_back(v.x);
                data.emplace_back(v.y);
                data.emplace_back(v.z);
            }
            glUniform3fv(it->second, value.size(), data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::vec4>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 4);
            for (auto& v : value)
            {
                data.emplace_back(v.x);
                data.emplace_back(v.y);
                data.emplace_back(v.z);
                data.emplace_back(v.w);
            }
            glUniform4fv(it->second, value.size(), data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat2>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 4);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
            }
            glUniformMatrix2fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat3>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 9);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[0][2]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[1][2]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
                data.emplace_back(v[2][2]);
            }
            glUniformMatrix3fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat4>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 16);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[0][2]);
                data.emplace_back(v[0][3]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[1][2]);
                data.emplace_back(v[1][3]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
                data.emplace_back(v[2][2]);
                data.emplace_back(v[2][3]);
                data.emplace_back(v[3][0]);
                data.emplace_back(v[3][1]);
                data.emplace_back(v[3][2]);
                data.emplace_back(v[3][3]);
            }
            glUniformMatrix4fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat2x3>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 6);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
            }
            glUniformMatrix2x3fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat2x4>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 8);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
                data.emplace_back(v[3][0]);
                data.emplace_back(v[3][1]);
            }
            glUniformMatrix2x4fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat3x2>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 6);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
            }
            glUniformMatrix3x2fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat3x4>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 12);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[0][2]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[1][2]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
                data.emplace_back(v[2][2]);
                data.emplace_back(v[3][0]);
                data.emplace_back(v[3][1]);
                data.emplace_back(v[3][2]);
            }
            glUniformMatrix3x4fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat4x2>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 8);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
                data.emplace_back(v[3][0]);
                data.emplace_back(v[3][1]);
            }
            glUniformMatrix4x2fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }

    void Shader::setUniform(const std::string& name, const std::vector<glm::mat4x3>& value)
    {
        if(!inUse())
        {
            lc::Log<GL>("ERROR", "Shader is not in use");
            return;
        }
        auto it = std::find_if(uniforms.begin(), uniforms.end(), [name](const auto& u) { return u.first.name == name; });
        if (it != uniforms.end())
        {
            std::vector<float> data;
            data.reserve(value.size() * 12);
            for (auto& v : value)
            {
                data.emplace_back(v[0][0]);
                data.emplace_back(v[0][1]);
                data.emplace_back(v[0][2]);
                data.emplace_back(v[1][0]);
                data.emplace_back(v[1][1]);
                data.emplace_back(v[1][2]);
                data.emplace_back(v[2][0]);
                data.emplace_back(v[2][1]);
                data.emplace_back(v[2][2]);
                data.emplace_back(v[3][0]);
                data.emplace_back(v[3][1]);
                data.emplace_back(v[3][2]);
            }
            glUniformMatrix4x3fv(it->second, value.size(), GL_FALSE, data.data());
        }
    }
}