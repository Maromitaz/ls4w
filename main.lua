project "main"
  kind "ConsoleApp"

  language "C"
  cdiallect "C17"

  targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.location}"
  objdir    "%{wks.location}/bin-int/%{cfg.buildcfg}/%{prj.location}"

  files {
    "%{wks.location}/src/main.c"
  }

  filter {"configuration:Debug"}
    defines { "DEBUG" }
    optimize "Debug"

  filter {"configuration:Release"}
    optimize "On"

  filter {"configuration:Dist"}
    optimize "Full"

  filter { "" }

