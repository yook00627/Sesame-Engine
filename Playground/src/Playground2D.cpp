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
    {
        SSM_PROFILE_SCOPE("Renderer Prep");
        Sesame::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
        Sesame::RenderCommand::Clear();
    }

    {
        SSM_PROFILE_SCOPE("Renderer Draw");
        Sesame::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Sesame::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
        Sesame::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.7f }, { 0.1f, 0.8f, 0.3f, 1.0f });
        //Sesame::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_DefaultTexture, 4.0f, m_TintColor);
        Sesame::Renderer2D::EndScene(); 
    }
}

void Playground2D::OnImGuiRender()
{
    SSM_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::ColorEdit4("Texture Color", glm::value_ptr(m_TintColor));
    ImGui::End();
}

void Playground2D::OnEvent(Sesame::Event& e)
{
    m_CameraController.OnEvent(e);
}
