workspace "tweather" 
    configurations { "Debug","Release" }
project "tweather"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    files { "src/**.h", "src/**.c" }
    links { "curl", "jansson" }
    filter "configurations:Debug" 
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:Release" 
        defines { "NDEBUG" }
        optimize "On"