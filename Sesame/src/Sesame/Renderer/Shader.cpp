#include "ssmpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sesame {

    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: SSM_CORE_ASSERT(false, "Shader API::None is not supported"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
        }

        SSM_CORE_ASSERT(false, "Shader API is unknown");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: SSM_CORE_ASSERT(false, "Shader API::None is not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        SSM_CORE_ASSERT(false, "Shader API is unknown");
        return nullptr;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        SSM_CORE_ASSERT(!Exists(name), "Shader already exists");
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        SSM_CORE_ASSERT(Exists(name), "Shader can't be found");
        return m_Shaders[name];
    }
    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}