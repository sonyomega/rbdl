	project "rbdl"
		
	kind "StaticLib"
	targetdir "../lib"
	includedirs {
		".",
	}
	files {
		"**.cc",
		"**.h"
	}
