#include "Playground2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Playground2D::Playground2D()
    : Layer("Playground2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Playground2D::OnAttach()
{
    m_VertexArray = Sesame::VertexArray::Create();

    float vertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f, 
        0.5f, 0.5f, 0.0f, 
        -0.5f, 0.5f, 0.0f
    };

    Sesame::Ref<Sesame::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(Sesame::VertexBuffer::Create(vertices, sizeof(vertices)));

    Sesame::BufferLayout layout = {
        { Sesame::ShaderDataType::Float3, "a_Position" }
    };
    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
    Sesame::Ref<Sesame::IndexBuffer> indexBuffer;
    indexBuffer.reset(Sesame::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareShader = Sesame::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Playground2D::OnDetach()
{
}

void Playground2D::OnUpdate(Sesame::Timestep ts)
{
    //Update
    m_CameraController.OnUpdate(ts);

    //Render
    Sesame::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
    Sesame::RenderCommand::Clear();

    Sesame::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Sesame::OpenGLShader>(m_SquareShader)->Bind();
    std::dynamic_pointer_cast<Sesame::OpenGLShader>(m_SquareShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    Sesame::Renderer::Submit(m_SquareShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Sesame::Renderer::EndScene();
}

void Playground2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Playground2D::OnEvent(Sesame::Event& e)
{
    m_CameraController.OnEvent(e);
}
