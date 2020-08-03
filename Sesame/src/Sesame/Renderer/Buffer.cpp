#include "ssmpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sesame {
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: SSM_CORE_ASSERT(false, "RednererAPI::None is not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(size);
        }

        SSM_CORE_ASSERT(false, "Renderer API is unknown");
        return nullptr;
    }
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: SSM_CORE_ASSERT(false, "RednererAPI::None is not supported"); return nullptr;
            case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        SSM_CORE_ASSERT(false, "Renderer API is unknown");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: SSM_CORE_ASSERT(false, "RednererAPI::None is not supported"); return nullptr;
        case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);
        }

        SSM_CORE_ASSERT(false, "Renderer API is unknown");
        return nullptr;
    }
}