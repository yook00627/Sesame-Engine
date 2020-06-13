workspace "Sesame"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Adding include paths relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Sesame/vendor/GLFW/include"
IncludeDir["Glad"] = "Sesame/vendor/GLAD/include"

-- Adding extra premake files
include "Sesame/vendor/GLFW"
include "Sesame/vendor/Glad"

project "Sesame"
    location "Sesame"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ssmpch.h"
    pchsource "Sesame/src/ssmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}"
    }

    links
    {
        "GLFW",
        "Glad",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "SSM_PLATFORM_WINDOWS",
            "SSM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Playground")
        }

    filter "configurations:Debug"
        defines "SSM_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "SSM_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "SSM_DIST"
        buildoptions "/MD"
        optimize "On"


project "Playground"
    location "Playground"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Sesame/vendor/spdlog/include",
        "Sesame/src"
    }

    links
    {
        "Sesame"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        
        defines
        {
            "SSM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SSM_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "SSM_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "SSM_DIST"
        buildoptions "/MD"
        optimize "On"
