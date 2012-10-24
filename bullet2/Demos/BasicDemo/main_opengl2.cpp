
#include "BasicDemo.h"

#ifdef __APPLE__
#include "../examples/rendertest/Apple/MacOpenGLWindow.h"
#else
#include "../examples/rendertest/Windows/Win32OpenGLWindow.h"
#include "../examples/rendertest/GLPrimitiveRenderer.h"
#endif
#include "../../DemosCommon/OpenGL2Renderer.h"

int g_OpenGLWidth=1024;
int g_OpenGLHeight = 768;



OpenGL2Renderer render;
void MyKeyboardCallback(int key, int state)
{
	if (state&1)
	{
		render.keyboardCallback(key);
	}
}


int main(int argc, char* argv[])
{


#ifdef __APPLE__
	MacOpenGLWindow* window = new MacOpenGLWindow();
#else
	Win32OpenGLWindow* window = new Win32OpenGLWindow();
#endif
	btgWindowConstructionInfo wci(g_OpenGLWidth,g_OpenGLHeight);
	wci.m_openglVersion = 2;	
	window->createWindow(wci);
	window->setWindowTitle("MyTest");
#ifdef _WIN32
	glewInit();
#endif

    
	window->startRendering();
	float color[4] = {1,1,1,1};
//	prim.drawRect(0,0,200,200,color);
	
    
	
	window->endRendering();

    
	
	window->setKeyboardCallback(MyKeyboardCallback);


	{
		BasicDemo* demo = new BasicDemo;
		demo->myinit();
		demo->initPhysics();
		
		do
		{
			window->startRendering();
			demo->clientMoveAndDisplay();

			render.init();
			render.renderPhysicsWorld(demo->getDynamicsWorld());
			window->endRendering();
		} while (!window->requestedExit());

		demo->exitPhysics();
		delete demo;
	}


	window->closeWindow();
	delete window;

	return 0;
}
