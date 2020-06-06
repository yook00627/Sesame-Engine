#pragma once

#ifdef  SSM_PLATFORM_WINDOWS

extern Sesame::Application* Sesame::CreateApplication();

int main(int argc, char** argv)
{
	printf("Welcome to Sesame");
	auto app = Sesame::CreateApplication();
	app->Run();
	delete app;
}

#endif