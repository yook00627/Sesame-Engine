#pragma once

#include "Core.h"
#include "Window.h"
#include "Sesame/LayerStack.h"
#include "Events/Event.h"
#include "Sesame/Events/ApplicationEvent.h"

#include "Sesame/ImGui/ImGuiLayer.h"

//temp
#include "Sesame/Renderer/Shader.h"
#include "Sesame/Renderer/Buffer.h"
#include "Sesame/Renderer/VertexArray.h"

#include "Sesame/Renderer/Camera.h"


namespace Sesame {

    class SESAME_API Application
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

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_ShaderSquare;
        std::shared_ptr<VertexArray> m_SquareVertexArray;

        OrthographicCamera m_Camera;
    private:
        static Application* s_Instance;
    };

    //Should be defined in Client
    Application* CreateApplication();
}
