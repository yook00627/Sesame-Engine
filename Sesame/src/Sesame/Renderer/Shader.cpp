#include "ssmpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sesame {

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: SSM_CORE_ASSERT(false, "Shader API::None is not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }

        SSM_CORE_ASSERT(false, "Shader API is unknown");
        return nullptr;
    }
}