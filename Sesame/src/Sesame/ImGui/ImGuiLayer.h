#pragma once

#include "Sesame/Core/Layer.h"
#include "Sesame/Events/MouseEvent.h"
#include "Sesame/Events/KeyEvent.h"
#include "Sesame/Events/ApplicationEvent.h"

namespace Sesame {

    class SESAME_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}