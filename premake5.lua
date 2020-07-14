workspace "Sesame"
    architecture "x64"
    startproject "Playground"

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
IncludeDir["ImGui"] = "Sesame/vendor/imgui"
IncludeDir["glm"] = "Sesame/vendor/glm"
IncludeDir["stb_image"] = "Sesame/vendor/stb_image"

-- Adding extra premake files
group "Dependencies"
    include "Sesame/vendor/GLFW"
    include "Sesame/vendor/Glad"
    include "Sesame/vendor/imgui"
group ""

project "Sesame"
    location "Sesame"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ssmpch.h"
    pchsource "Sesame/src/ssmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        
        defines
        {
            "SSM_PLATFORM_WINDOWS",
            "SSM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "SSM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SSM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "SSM_DIST"
        runtime "Release"
        optimize "on"


project "Playground"
    location "Playground"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Sesame/src",
        "Sesame/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Sesame"
    }

    filter "system:windows"
        systemversion "latest"
        
        defines
        {
            "SSM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SSM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SSM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "SSM_DIST"
        runtime "Release"
        optimize "on"
