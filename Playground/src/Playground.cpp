#include <Sesame.h>

class NewLayer : public Sesame::Layer
{
public:
    NewLayer()
        : Layer("New") {}

    void OnUpdate() override
    {
        if (Sesame::Input::IsKeyPressed(SSM_KEY_TAB))
            SSM_TRACE("TAB key is pressed");
    }

    void OnEvent(Sesame::Event& event) override
    {
        //SSM_TRACE("{0}", event);
        if (event.GetEventType() == Sesame::EventType::KeyPressed)
        {
            Sesame::KeyPressedEvent& e = (Sesame::KeyPressedEvent&)event;
            SSM_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
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