workspace "ls4w"
  configurations { "Debug", "Release", "Dist" }

project "ls"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"

  targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.location}"
  objdir    "%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.location}"

  files {
    "%{prj.location}/src/ghc/filesystem.hpp",
    "%{prj.location}/src/main.cpp"
  }

  filter "configurations:Debug"
      defines {"DEBUG"}
      symbols "On"

  filter "configurations:Release"
      defines {"NDEBUG"}
      optimize "On"
