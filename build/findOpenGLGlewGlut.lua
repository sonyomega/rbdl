
	function initOpenGL()
		configuration {}
		configuration {"Windows"}
			links {"opengl32","glu32"}
		configuration {"MacOSX"}
 			links { "OpenGL.framework"} 
		configuration {"not Windows", "not MacOSX"}
			links {"GL","GLU"}
		configuration{}
	end


	function initGlew()
		configuration {}
		configuration {"Windows"}
			defines { "GLEW_STATIC"}
			includedirs {
					projectRootDir .. "examples/rendertest/Windows"
			}
			libdirs {	projectRootDir .. "examples/rendertest/Windows"}
		configuration {"Windows", "x32"}
			links {"glew32s"}
		configuration {"Windows", "x64"}
			links {"glew64s"}

		configuration{}
	end



