/*
Copyright (c) 2012 Advanced Micro Devices, Inc.  

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
//Originally written by Erwin Coumans

//
//#include "vld.h"
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <assert.h>

#include "GLInstancingRenderer.h"

#ifdef __APPLE__
#include "MacOpenGLWindow.h"
#else
#include "Win32OpenGLWindow.h"
#endif
btgDefaultOpenGLWindow* sWindow=0;


#include "GLPrimitiveRenderer.h"

#include "RenderScene.h"
#include "LinearMath/btQuickprof.h"
#include "LinearMath/btQuaternion.h"
#include "CommandlineArgs.h"
#include "fontstash.h"
#include "opengl_fontstashcallbacks.h"


bool printStats = false;
bool pauseSimulation = false;
bool shootObject = true;
bool useInterop = false;


void MyKeyboardCallback(int keycode, int state)
{
	int ch = keycode;
	printf("char=%d", ch);
	if (keycode==BTG_ESCAPE)
	{
		sWindow->setRequestExit();
	}

	if (state&1)
	{
		printf("pressed\n");
	} else
	{
		printf("released\n");
	}
}

void MyMouseButtonCallback(int button, int state, float x, float y)
{
//	printf("mouse button = button=%d, state=%d,x=%f,y=%f\n", button,state,x,y);
	btDefaultMouseButtonCallback(button,state,x,y);
}

int g_OpenGLWidth = 1024;
int g_OpenGLHeight =768;

void MyResizeCallback(float width, float height)
{
	g_OpenGLWidth = width;
	g_OpenGLHeight = height;
}

void MyMouseMoveCallback( float x, float y)
{
//	printf("mouse move = %f,%f\n", x,y);
	btDefaultMouseMoveCallback(x,y);

}


int droidRegular, droidItalic, droidBold, droidJapanese, dejavu;

sth_stash* initFont();

extern int test();

int main(int argc, char* argv[])
{
		
	int val = test();
	
	CommandLineArgs args(argc,argv);
//	args.GetCmdLineArgument("pause_simulation", pauseSimulation);
	
	btgDefaultOpenGLWindow* window = new btgDefaultOpenGLWindow();
	sWindow = window;
	
	window->createDefaultWindow(g_OpenGLWidth,g_OpenGLHeight,"test");

	window->setWindowTitle("blaat");
	
    float retinaScale = 1;
    
#ifndef __APPLE__
	GLenum err = glewInit();
#else
    retinaScale = window->getRetinaScale();
#endif
    
    window->runMainLoop();
	window->startRendering();
	window->endRendering();

	int maxObjectCapacity=128*1024;
	GLInstancingRenderer render(maxObjectCapacity);

	
	sth_stash* stash = initFont();
		
	render.InitShaders();


	createSceneProgrammatically(render);
    

	render.writeTransforms();

    window->runMainLoop();

	window->setMouseButtonCallback(MyMouseButtonCallback);
	window->setMouseMoveCallback(MyMouseMoveCallback);
	window->setResizeCallback(MyResizeCallback);
	window->setKeyboardCallback(MyKeyboardCallback);
    window->setWheelCallback(btDefaultWheelCallback);


    GLPrimitiveRenderer* pprender = new GLPrimitiveRenderer(g_OpenGLWidth,g_OpenGLHeight);
   
   glUseProgram(0); 


	class CProfileIterator* m_profileIterator;
	m_profileIterator = CProfileManager::Get_Iterator();

	glClearColor(1,1,1,1);
	while (!window->requestedExit())
	{
		CProfileManager::Reset();
	
		BT_PROFILE("loop");

		{
			BT_PROFILE("startRendering");
			window->startRendering();
		}
		render.RenderScene();
		glFinish();
		float col[4]={0,1,0,1};
//             glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_TEXTURE_2D);


		float x = 10;
		float y=220;
		float  dx=0;
		glDisable(GL_DEPTH_TEST);

		if (retinaScale!=1.f)
			pprender->drawRect(x,y,x+720,y+120,col);
		else
			pprender->drawRect(x,y,x+720,y+60,col);
		
		
		if (1)
		{
			BT_PROFILE("font sth_draw_text");
			
			sth_begin_draw(stash);
			sth_flush_draw(stash);

			sth_draw_text(stash, droidRegular,40.f, x, y, "Non-retina font rendering !@#$", &dx,g_OpenGLWidth,g_OpenGLHeight,0,1);//retinaScale);
			if (retinaScale!=1.f)
				sth_draw_text(stash, droidRegular,40.f*retinaScale, x, y+20, "Retina font rendering!@#$", &dx,g_OpenGLWidth,g_OpenGLHeight,0,retinaScale);
			sth_flush_draw(stash);
			
			sth_end_draw(stash);
		}

		if (1)
		{
			BT_PROFILE("gwen RenderCanvas");
	
		}

		window->endRendering();
		
		CProfileManager::Increment_Frame_Counter();

		static bool printStats  = true;
		
		 if (printStats && !pauseSimulation)
		 {
			static int count = 0;
			count--;
			if (count<0)
			{
				count = 100;
				{
					//BT_PROFILE("processProfileData");
				}
				//CProfileManager::dumpAll();
				//printStats  = false;
			} else
			{
//				printf(".");
			}
		 }
		
	}

	delete pprender;
	render.CleanupShaders();
	window->closeWindow();

	delete window;
	return 0;
}


sth_stash* initFont()
{
	GLint err;

		struct sth_stash* stash = 0;
	int datasize;
	unsigned char* data;
	stash = sth_create(512,512,OpenGL2UpdateTextureCallback,OpenGL2RenderCallback);//256,256);//,1024);//512,512);
    err = glGetError();
    assert(err==GL_NO_ERROR);
    
	if (!stash)
	{
		fprintf(stderr, "Could not create stash.\n");
		return 0;
	}

	const char* fontPaths[]={
	"./",
	"../../bin/",
	"../bin/",
	"bin/"
	};

	int numPaths=sizeof(fontPaths)/sizeof(char*);
	
	// Load the first truetype font from memory (just because we can).
    
	FILE* fp = 0;
	const char* fontPath ="./";
	char fullFontFileName[1024];

	for (int i=0;i<numPaths;i++)
	{
		
		fontPath = fontPaths[i];
		//sprintf(fullFontFileName,"%s%s",fontPath,"OpenSans.ttf");//"DroidSerif-Regular.ttf");
		sprintf(fullFontFileName,"%s%s",fontPath,"DroidSerif-Regular.ttf");//OpenSans.ttf");//"DroidSerif-Regular.ttf");
		fp = fopen(fullFontFileName, "rb");
		if (fp)
			break;
	}

    err = glGetError();
    assert(err==GL_NO_ERROR);
    
    assert(fp);
    if (fp)
    {
        fseek(fp, 0, SEEK_END);
        datasize = (int)ftell(fp);
        fseek(fp, 0, SEEK_SET);
        data = (unsigned char*)malloc(datasize);
        if (data == NULL)
        {
            assert(0);
            return 0;
        }
        else
            fread(data, 1, datasize, fp);
        fclose(fp);
        fp = 0;
    }
	if (!(droidRegular = sth_add_font_from_memory(stash, data)))
    {
        assert(0);
        return 0;
    }
    err = glGetError();
    assert(err==GL_NO_ERROR);

	// Load the remaining truetype fonts directly.
    sprintf(fullFontFileName,"%s%s",fontPath,"DroidSerif-Italic.ttf");

	if (!(droidItalic = sth_add_font(stash,fullFontFileName)))
	{
        assert(0);
        return 0;
    }
     sprintf(fullFontFileName,"%s%s",fontPath,"DroidSerif-Bold.ttf");

	if (!(droidBold = sth_add_font(stash,fullFontFileName)))
	{
        assert(0);
        return 0;
    }
    err = glGetError();
    assert(err==GL_NO_ERROR);
    
     sprintf(fullFontFileName,"%s%s",fontPath,"DroidSansJapanese.ttf");
    if (!(droidJapanese = sth_add_font(stash,fullFontFileName)))
	{
        assert(0);
        return 0;
    }
    err = glGetError();
    assert(err==GL_NO_ERROR);

	return stash;
}
