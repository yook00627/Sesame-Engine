#include "ssmpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Sesame {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Sesame::ShaderDataType::Float: return GL_FLOAT;
            case Sesame::ShaderDataType::Float2: return GL_FLOAT;
            case Sesame::ShaderDataType::Float3: return GL_FLOAT;
            case Sesame::ShaderDataType::Float4: return GL_FLOAT;
            case Sesame::ShaderDataType::Mat3: return GL_FLOAT;
            case Sesame::ShaderDataType::Mat4: return GL_FLOAT;
            case Sesame::ShaderDataType::Int: return GL_INT;
            case Sesame::ShaderDataType::Int2: return GL_INT;
            case Sesame::ShaderDataType::Int3: return GL_INT;
            case Sesame::ShaderDataType::Int4: return GL_INT;
            case Sesame::ShaderDataType::Bool: return GL_BOOL;
        }
        SSM_CORE_ASSERT(false, "ShaderDataType unkown");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        SSM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer needs layouts");
        
        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)(intptr_t)element.Offset);
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}