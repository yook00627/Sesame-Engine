#include <Sesame.h>

class NewLayer : public Sesame::Layer
{
public:
    NewLayer()
        : Layer("New") {}

    void OnUpdate() override
    {
        //SSM_INFO("Exmpale for updating Layer");
    }

    void OnEvent(Sesame::Event& event) override
    {
        SSM_TRACE("{0}", event);
    }
};

class Playground : public Sesame::Application
{
public:
    Playground()
    {
        PushLayer(new NewLayer());
        PushOverlay(new Sesame::ImGuiLayer());
    }

    ~Playground()
    {
    }
};

Sesame::Application* Sesame::CreateApplication()
{
    return new Playground();
}