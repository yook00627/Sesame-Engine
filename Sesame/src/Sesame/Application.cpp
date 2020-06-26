#include "ssmpch.h"
#include "Application.h"

#include "Sesame/Log.h"

#include <glad/glad.h>

namespace Sesame {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        SSM_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(SSM_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer(); 
        PushOverlay(m_ImGuiLayer);

        // temp just added to see if it runs
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = { 0, 1 ,2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 a_Color;

            in vec3 v_Position;
            
            void main()
            {
                a_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";

        // shader
        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }
    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(SSM_BIND_EVENT_FN(Application::OnWindowClose));

        // Logging test
        //SSM_CORE_INFO("{0}", e);

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}
