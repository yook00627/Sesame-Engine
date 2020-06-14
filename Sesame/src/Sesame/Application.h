#pragma once

#include "Core.h"
#include "Window.h"
#include "Sesame/LayerStack.h"
#include "Events/Event.h"
#include "Sesame/Events/ApplicationEvent.h"

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
        bool m_Running = true;
        LayerStack m_LayerStack;
    private:
        static Application* s_Instance;
    };

    //Should be defined in Client
    Application* CreateApplication();
}
