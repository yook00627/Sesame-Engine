#pragma once

#include "Sesame.h"

class Playground2D : public Sesame::Layer
{
public:
    Playground2D();
    virtual ~Playground2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Sesame::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Sesame::Event& e) override;
private:
    Sesame::OrthographicCameraController m_CameraController;

    //Temp
    Sesame::Ref<Sesame::VertexArray> m_VertexArray;
    Sesame::Ref<Sesame::Shader> m_SquareShader;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};