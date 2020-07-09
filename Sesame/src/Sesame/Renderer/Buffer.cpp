#include "ssmpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sesame {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: SSM_CORE_ASSERT(false, "RednererAPI::None is not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }

        SSM_CORE_ASSERT(false, "Renderer API is unknown");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: SSM_CORE_ASSERT(false, "RednererAPI::None is not supported"); return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }

        SSM_CORE_ASSERT(false, "Renderer API is unknown");
        return nullptr;
    }
}