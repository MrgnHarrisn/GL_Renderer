project "stb_image"
    kind "StaticLib"
    language "C"
    staticruntime "On"
    architecture "x86_64"

    targetdir "../bin/%{cfg.buildcfg}"
    objdir "../obj/%{cfg.buildcfg}"
    
    includedirs { 
        "stb/",
        "../include",
        "../vendor/GLAD/include"
    }


    files { "../include/stb_image_wrapper.h" }
    

    filter "configurations:Debug"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release"
        optimize "On"
        runtime "Release"