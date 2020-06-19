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

-- Adding extra premake files
group "Dependencies"
    include "Sesame/vendor/GLFW"
    include "Sesame/vendor/Glad"
    include "Sesame/vendor/imgui"
group ""

project "Sesame"
    location "Sesame"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "ssmpch.h"
    pchsource "Sesame/src/ssmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        defines
        {
            "SSM_PLATFORM_WINDOWS",
            "SSM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Playground/\"")
        }

    filter "configurations:Debug"
        defines "SSM_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "SSM_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "SSM_DIST"
        runtime "Release"
        optimize "On"


project "Playground"
    location "Playground"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        "%{IncludeDir.glm}"
    }

    links
    {
        "Sesame"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        defines
        {
            "SSM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "SSM_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "SSM_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "SSM_DIST"
        runtime "Release"
        optimize "On"
