#include "ssmpch.h"
#include "Application.h"

#include "Sesame/Renderer/Renderer.h"

namespace Sesame {

    Application* Application::s_Instance = nullptr;

    Application::Application()
        : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
        SSM_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(SSM_BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer(); 
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        };

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);



        m_SquareVertexArray.reset(VertexArray::Create());

        float squareVertices[3 * 7] = {
            -0.65f, -0.65f, 0.0f,
            0.65f, -0.65f, 0.0f,
            0.65f, 0.65f, 0.0f,
            -0.65f, 0.65f, 0.0f
        };

        std::shared_ptr<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        BufferLayout squareLayout = {
            { ShaderDataType::Float3, "a_Position" }
        };
        squareVertexBuffer->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);


        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            out vec4 v_Color;
            
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;
            
            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        std::string vertexSrcSquare = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrcSquare = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            
            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";

        m_ShaderSquare.reset(new Shader(vertexSrcSquare, fragmentSrcSquare));
    }
    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
            RenderCommand::Clear();
            
            m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
            m_Camera.SetRotation(45.0f);

            Renderer::BeginScene(m_Camera);

            Renderer::Submit(m_ShaderSquare, m_SquareVertexArray);
            Renderer::Submit(m_Shader, m_VertexArray);

            Renderer::EndScene();

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
