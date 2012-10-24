	
	

		project "OpenGL_rendertest"

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
		
			
		links {"rbdl"}
		links { "Cocoa.framework" }
		
		files {
			"../main.cpp",
			"../rbdlSimulation.cpp",
			"../renderscene.cpp",
			"../renderscene.h",
			"../btConvexUtility.cpp",
			"../btConvexUtility.h",
			"MacOpenGLWindow.h",
			"MacOpenGLWindow.mm",
			"../btgWindowInterface.h",
			"../GLInstancingRenderer.cpp",
			"../GLInstancingRenderer.h",
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
		
