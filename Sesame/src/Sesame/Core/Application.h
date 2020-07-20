#pragma once

#include "Core.h"
#include "Window.h"
#include "Sesame/Core/LayerStack.h"
#include "Sesame/Events/Event.h"
#include "Sesame/Events/ApplicationEvent.h"

#include "Sesame/Core/Timestep.h"

#include "Sesame/ImGui/ImGuiLayer.h"
#include "Sesame/Renderer/Renderer.h"

namespace Sesame {

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    //Should be defined in Client
    Application* CreateApplication();
}