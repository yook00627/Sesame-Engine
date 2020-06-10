#include "ssmpch.h"
#include "Application.h"

#include "Sesame/Events/ApplicationEvent.h"
#include "Sesame/Log.h"

namespace Sesame {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			SSM_TRACE(e);
		}
		while (true);
	}
}
