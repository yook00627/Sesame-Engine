#include "ssmpch.h"
#include "Application.h"

#include "Sesame/Events/ApplicationEvent.h"
#include "Sesame/Log.h"

namespace Sesame {
    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }
    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }
}
