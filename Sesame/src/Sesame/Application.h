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

        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    private:
        static Application* s_Instance;
    };

    //Should be defined in Client
    Application* CreateApplication();
}
