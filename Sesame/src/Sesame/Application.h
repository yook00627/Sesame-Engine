#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Sesame {

	class SESAME_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//Should be defined in Client
	Application* CreateApplication();
}
