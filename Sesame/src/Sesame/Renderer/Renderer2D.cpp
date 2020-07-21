#include "ssmpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Sesame {

    struct Renderere2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> FlatColorShader;
    };

    static Renderere2DStorage* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new Renderere2DStorage();
        s_Data->QuadVertexArray = VertexArray::Create();

        float vertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
        };

        Ref<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
        });
        s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

        s_Data->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }

    void Renderer2D::EndScene()
    {

    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        Renderer2D::DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", color);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }
}