#pragma once

#include "Sesame/Core/Core.h"
#include "Sesame/Core/Timestep.h"
#include "Sesame/Events/Event.h"

namespace Sesame {

    class SESAME_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        std::string m_DebugName;
    };
}