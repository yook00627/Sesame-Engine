#include "ssmpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Sesame {

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: SSM_CORE_ASSERT(false, "RednererAPI::None is not supported"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }

        SSM_CORE_ASSERT(false, "Renderer API is unknown");
        return nullptr;
    }
}