#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Sesame/Events/ApplicationEvent.h"

namespace Sesame {

    class SESAME_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    //Should be defined in Client
    Application* CreateApplication();
}
