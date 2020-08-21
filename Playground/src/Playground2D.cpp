#include "Playground2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

Playground2D::Playground2D()
    : Layer("Playground2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Playground2D::OnAttach()
{
    SSM_PROFILE_FUNCTION();

    m_DefaultTexture = Sesame::Texture2D::Create("assets/textures/default.png");
}

void Playground2D::OnDetach()
{
    SSM_PROFILE_FUNCTION();
}

void Playground2D::OnUpdate(Sesame::Timestep ts)
{
    SSM_PROFILE_FUNCTION();

    //Update
    m_CameraController.OnUpdate(ts);

    //Render
    Sesame::Renderer2D::ResetStats();
    {
        SSM_PROFILE_SCOPE("Renderer Prep");
        Sesame::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Sesame::RenderCommand::Clear();
    }

    {
        static float rotation = 0.0f;
        rotation += ts * 50.0f;

        SSM_PROFILE_SCOPE("Renderer Draw");
        Sesame::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Sesame::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
        Sesame::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
        Sesame::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.1f, 0.8f, 0.3f, 1.0f });
        Sesame::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_DefaultTexture, 5.0f);
        Sesame::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_DefaultTexture, 1.0f);
        Sesame::Renderer2D::EndScene();

        Sesame::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
                Sesame::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }
        Sesame::Renderer2D::EndScene();
    }
}

void Playground2D::OnImGuiRender()
{
    SSM_PROFILE_FUNCTION();

    ImGui::Begin("Settings");

    auto stats = Sesame::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Playground2D::OnEvent(Sesame::Event& e)
{
    m_CameraController.OnEvent(e);
}
