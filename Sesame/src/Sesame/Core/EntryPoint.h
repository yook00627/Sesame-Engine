#pragma once

#ifdef SSM_PLATFORM_WINDOWS

extern Sesame::Application* Sesame::CreateApplication();

int main(int argc, char** argv)
{
    Sesame::Log::Init();

    SSM_PROFILE_BEGIN_SESSION("Starting", "SesameProfile_Startup.json");
    auto app = Sesame::CreateApplication();
    SSM_PROFILE_END_SESSION();

    SSM_PROFILE_BEGIN_SESSION("Starting", "SesameProfile_Runtime.json");
    app->Run();
    SSM_PROFILE_END_SESSION();

    SSM_PROFILE_BEGIN_SESSION("Starting", "SesameProfile_Shutdown.json");
    delete app;
    SSM_PROFILE_END_SESSION();
}

#endif