#include "gfx.hpp"
#include <glad/glad.h>
#include <lc.hpp>
#include <logConfig.hpp>

namespace gfx
{
    static TextureBindingMode bindingMode = TextureBindingMode::NONE;
    static uint64_t maxUBOSiumultaneousBindings = 0;

    static void GLDebugCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
            return;

        std::string sourceStr;
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            sourceStr = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceStr = "WINDOW SYSTEM";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceStr = "SHADER COMPILER";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceStr = "THIRD PARTY";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            sourceStr = "APPLICATION";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            sourceStr = "OTHER";
            break;
        }

        std::string typeStr;
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "DEPRECATED BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "UNDEFINED BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            typeStr = "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeStr = "MARKER";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeStr = "PUSH GROUP";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            typeStr = "POP GROUP";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeStr = "OTHER";
            break;
        }

        std::string severityStr;
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            severityStr = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityStr = "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityStr = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityStr = "NOTIFICATION";
            break;
        }

        lc::Log("OPENGL", "{} {} {} {} {}", sourceStr, typeStr, id, severityStr, message);
    }

    bool Init(loadproc getProcAddress, TextureBindingMode mode)
    {
        auto load = gladLoadGLLoader(getProcAddress);
        if (load)
        {
            lc::Init();

            lc::AddLogType("OPENGL");
            lc::SetLogColorLevel("OPENGL", lc::LogColor::Red, {lc::LogEffect::Bold});
            lc::SetLogColorMessage("OPENGL", true);
            lc::SetLogColorMessage("OPENGL", lc::LogColor::Red);
            lc::SetFormat("OPENGL", "[{LEVEL}] {MSG}");

            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(GLDebugCallBack, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

            glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, (GLint*)&maxUBOSiumultaneousBindings);

            SetTextureBindingMode(mode);
        }
        return load;
    }

    void DeInit()
    {}

    void Clear(float r, float g, float b, float a, int clearFlags)
    {
        glClear(clearFlags);
        glClearColor(r, g, b, a);
    }

    void PrintVRVOpenGL()
    {
        std::string glVendor((const char*)glGetString(GL_VENDOR));
        std::string glRenderer((const char*)glGetString(GL_RENDERER));
        std::string glVersion((const char*)glGetString(GL_VERSION));
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Vendor: {}", glVendor);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Renderer: {}", glRenderer);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Version: {}", glVersion);
    }

    void PrintSupportedOpenGLFeatures()
    {
        GLint numExtensions;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        lc::Log<"GFX BUILD">("DEBUG", "OpenGL Extensions: {}", numExtensions);
        for (int i = 0; i < numExtensions; i++)
        {
            lc::Log<"GFX BUILD">("DEBUG", "OpenGL Extension: {}", (const char*)glGetStringi(GL_EXTENSIONS, i));
        }
    }

    bool CheckSupoortedOpenGLFeature(const char* feature)
    {
        GLint numExtensions;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        for (int i = 0; i < numExtensions; i++)
        {
            if (strcmp((const char*)glGetStringi(GL_EXTENSIONS, i), feature) == 0)
                return true;
        }
        return false;
    }

    void WireFrameMode(bool mode)
    {
        if (mode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void SetTextureBindingMode(TextureBindingMode mode)
    {
        if(mode == TextureBindingMode::BINDLESS)
        {
            if(CheckSupoortedOpenGLFeature(BINDLES_TEXTURE))
            {
                bindingMode = mode;
                lc::Log<"GFX BUILD">("DEBUG", "Bindless texture mode enabled");
            }
            else
                lc::Log<"GFX BUILD">("WARNING", "Bindless texture mode not supported! Falling back to bind mode");
        }
        else
        {
            bindingMode = mode;
            lc::Log<"GFX BUILD">("DEBUG", "Bind texture mode enabled");
        }
    }

    TextureBindingMode GetTextureBindingMode()
    {
        return bindingMode;
    }

    uint64_t GetMaxUBOSiumultaneousBindings()
    {
        return maxUBOSiumultaneousBindings;
    }

    void SetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void EnableDepthTest(int depthTestFuncFlag)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(depthTestFuncFlag);
    }

    void DisableDepthTest()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void EnableBlend(int blend, int blendFuncFlag)
    {
        glEnable(GL_BLEND);
        glBlendFunc(blend, blendFuncFlag);
    }

    void DisableBlend()
    {
        glDisable(GL_BLEND);
    }

    void EnableFaceCulling(int cullFace, int frontFace)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(cullFace);
        glFrontFace(frontFace);
    }

    void DisableFaceCulling()
    {
        glDisable(GL_CULL_FACE);
    }

    void EnableStencilTest(int stencilTest, int stencilFuncFlag, int stencilOpFlag)
    {
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(stencilFuncFlag, 1, 0xFF);
        glStencilOp(stencilOpFlag, stencilOpFlag, stencilOpFlag);
    }

    void DisableStencilTest()
    {
        glDisable(GL_STENCIL_TEST);
    }
}