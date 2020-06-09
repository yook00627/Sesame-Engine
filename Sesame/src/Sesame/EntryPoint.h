#pragma once

#ifdef  SSM_PLATFORM_WINDOWS

extern Sesame::Application* Sesame::CreateApplication();

int main(int argc, char** argv)
{
	Sesame::Log::Init();
	SSM_CORE_WARN("Getting ready");
	int a = 11;
	SSM_CORE_INFO("client number: {0}", a);

	auto app = Sesame::CreateApplication();
	app->Run();
	delete app;
}

#endif