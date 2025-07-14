workspace "OpenGL_Renderer"
    configurations { "Debug", "Release" }
    startproject "GLRenderer"

    flags {
        "MultiProcessorCompile"
    }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"

project "GLRenderer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs { 
        "include/",
        "vendor/glad/include",
        "vendor/glfw/include",
        "vendor/glm/",
        "vendor/imgui/",
        "vendor/imgui/examples",
    }

    files { "src/**.cpp", "include/**.h" }

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "system:linux"
        links { "d1", "pthread" }
        defines { "_X11" }
    
    filter "system:windows"
        defines { "_WINDOWS" }

include "vendor/glfw.lua"
include "vendor/glad.lua"
include "vendor/glm.lua"
include "vendor/imgui.lua"