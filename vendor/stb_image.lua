project "stb_image"
    kind "StaticLib"
    language "C" 
    staticruntime "On"
    architecture "x86_64"

    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"
    
    includedirs { 
        "stb/",
        "glad/include",
        "../include"
    }

    files { "stb/stb_image_impl.cpp" }
    
    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"