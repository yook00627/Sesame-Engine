#include "ssmpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Sesame/Platform/OpenGL/OpenGLVertexArray.h"

namespace Sesame {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: SSM_CORE_ASSERT(false, "RednererAPI::None is not supported"); return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }

        SSM_CORE_ASSERT(false, "Renderer API is unknown");
        return nullptr;
    }
}