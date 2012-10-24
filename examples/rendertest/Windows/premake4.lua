	
	
		project "OpenGL_rendertest"

		initOpenCL_NVIDIA()
	
		language "C++"
				
		kind "ConsoleApp"
		targetdir "../../../bin"


		initOpenGL()
		initGlew()

		includedirs {
		 ".",
			"../../../bullet2",
			"../../../src"
		}
		
		links {
			"rbdl"
		}
		
		files {
			"../main.cpp",
			"../renderscene.cpp",
			"../renderscene.h",
			"../rbdlSimulation.cpp",
			"../GLInstancingRenderer.cpp",
			"../GLInstancingRenderer.h",
			"Win32OpenGLWindow.cpp",
			"Win32OpenGLWindow.h",	
			"Win32Window.cpp",
			"Win32Window.h",
			"../btgWindowInterface.h",
			"../GLPrimitiveRenderer.h",
			"../GLPrimitiveRenderer.cpp",
			"../LoadShader.cpp",
			"../LoadShader.h",
			"../TwFonts.cpp",
			"../TwFonts.h",
			"../fontstash.cpp",
			"../fontstash.h",
			"../opengl_fontstashcallbacks.cpp",
 			"../opengl_fontstashcallbacks.h",
			"../../../bullet2/LinearMath/btConvexHullComputer.cpp",
			"../../../bullet2/LinearMath/btConvexHullComputer.h",
			"../../../bullet2/LinearMath/btSerializer.cpp",
			"../../../bullet2/LinearMath/btSerializer.h",
			"../../../bullet2/LinearMath/btAlignedAllocator.cpp",
			"../../../bullet2/LinearMath/btQuickprof.cpp",
			"../../../bullet2/LinearMath/btQuickprof.h"
		}
		
