#include <Sesame.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class NewLayer : public Sesame::Layer
{
public:
    NewLayer()
        : Layer("New"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
        m_VertexArray.reset(Sesame::VertexArray::Create());

        float vertices[7 * 3] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        };

        Sesame::Ref<Sesame::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Sesame::VertexBuffer::Create(vertices, sizeof(vertices)));

        Sesame::BufferLayout layout = {
            { Sesame::ShaderDataType::Float3, "a_Position" },
            { Sesame::ShaderDataType::Float4, "a_Color" },
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        Sesame::Ref<Sesame::IndexBuffer> indexBuffer;
        indexBuffer.reset(Sesame::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);



        m_SquareVertexArray.reset(Sesame::VertexArray::Create());

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        Sesame::Ref<Sesame::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(Sesame::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Sesame::BufferLayout squareLayout = {
            { Sesame::ShaderDataType::Float3, "a_Position" },
            { Sesame::ShaderDataType::Float2, "a_TexCord" }
        };
        squareVertexBuffer->SetLayout(squareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Sesame::Ref<Sesame::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Sesame::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);


        std::string vertexSrc = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            out vec4 v_Color;
            
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

        m_Shader.reset(Sesame::Shader::Create(vertexSrc, fragmentSrc));

        std::string vertexSrcSquare = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrcSquare = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec3 u_Color;
            
            void main()
            {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_ShaderSquare.reset(Sesame::Shader::Create(vertexSrcSquare, fragmentSrcSquare));

        std::string vertexSrcTexture = R"(
            #version 460 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCord;
            
            void main()
            {
                v_TexCord = a_TexCord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrcTexture = R"(
            #version 460 core

            layout(location = 0) out vec4 color;

            in vec2 v_TexCord;

            uniform sampler2D u_Texture;
            
            void main()
            {
                color = texture(u_Texture, v_TexCord);
            }
        )";

        m_TextureShader.reset(Sesame::Shader::Create(vertexSrcTexture, fragmentSrcTexture));

        m_Texture = Sesame::Texture2D::Create("assets/textures/default.png");

        std::dynamic_pointer_cast<Sesame::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Sesame::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Sesame::Timestep ts) override
    {
        if (Sesame::Input::IsKeyPressed(SSM_KEY_A))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        else if (Sesame::Input::IsKeyPressed(SSM_KEY_D))
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        if (Sesame::Input::IsKeyPressed(SSM_KEY_S))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        else if (Sesame::Input::IsKeyPressed(SSM_KEY_W))
            m_CameraPosition.y += m_CameraMoveSpeed * ts;

        if (Sesame::Input::IsKeyPressed(SSM_KEY_Q))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        if (Sesame::Input::IsKeyPressed(SSM_KEY_E))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

        Sesame::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
        Sesame::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Sesame::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Sesame::OpenGLShader>(m_ShaderSquare)->Bind();
        std::dynamic_pointer_cast<Sesame::OpenGLShader>(m_ShaderSquare)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), pos) * scale;
                Sesame::Renderer::Submit(m_ShaderSquare, m_SquareVertexArray, transfrom);

            }
        }

        m_Texture->Bind();
        Sesame::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Triangle
        // Sesame::Renderer::Submit(m_Shader, m_VertexArray);

        Sesame::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Sesame::Event& event) override
    {
        //Sesame::EventDispatcher dispatcher(event);
        //dispatcher.Dispatch<Sesame::KeyPressedEvent>(SSM_BIND_EVENT_FN(NewLayer::OnKeyPressedEvent));
    }

    //bool OnKeyPressedEvent(Sesame::KeyPressedEvent& event)
    //{
    //    if (event.GetKeyCode() == SSM_KEY_LEFT)
    //        m_CameraPosition.x -= m_CameraSpeed;
    //    if (event.GetKeyCode() == SSM_KEY_RIGHT)
    //        m_CameraPosition.x += m_CameraSpeed;
    //    if (event.GetKeyCode() == SSM_KEY_DOWN)
    //        m_CameraPosition.y -= m_CameraSpeed;
    //    if (event.GetKeyCode() == SSM_KEY_UP)
    //        m_CameraPosition.y += m_CameraSpeed;

    //    return false;
    //}
private:
    Sesame::Ref<Sesame::Shader> m_Shader;
    Sesame::Ref<Sesame::VertexArray> m_VertexArray;

    Sesame::Ref<Sesame::Shader> m_ShaderSquare, m_TextureShader;
    Sesame::Ref<Sesame::VertexArray> m_SquareVertexArray;

    Sesame::Ref<Sesame::Texture2D> m_Texture;

    Sesame::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 45.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Playground : public Sesame::Application
{
public:
    Playground()
    {
        PushLayer(new NewLayer());
    }

    ~Playground()
    {
    }
};

Sesame::Application* Sesame::CreateApplication()
{
    return new Playground();
}