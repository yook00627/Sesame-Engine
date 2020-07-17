#pragma once

#include "Renderer/Camera.h"
#include "Sesame/Core/Timestep.h"

#include "Sesame/Events/ApplicationEvent.h"
#include "Sesame/Events/MouseEvent.h"

namespace Sesame {

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraTranslationSpeed = 5.0f;
        float m_CameraRotation = 0.0f;
        float m_CameraRotationSpeed = 90.0f;
    };
}