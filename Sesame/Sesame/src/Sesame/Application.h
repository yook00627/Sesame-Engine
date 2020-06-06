#pragma once

#include "Core.h"


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
