#include <GL/glew.h>
#include "Typedefs.h"
#include "Settings.h"
#include "Game.h"
#include "Renderer/Renderer.h"
#include "OpenGL/OGLSurface.h"
#include "Stopwatch/Stopwatch.h"
#include <SFML/Window.h>

// global variables
bool g_isWindowOpen = true;


void handleWindowEvents( sfWindow* window)
{
	// variables
	sfEvent windowEvent;

	// handle events
	g_isWindowOpen = sfWindow_isOpen( window);
	while( sfWindow_pollEvent( window, &windowEvent))
	{
		switch( windowEvent.type)
		{
			case sfEvtClosed:
				g_isWindowOpen = false;
			break;
			case sfEvtGainedFocus:
				sfWindow_setFramerateLimit(window, 0);
			break;
			case sfEvtLostFocus:
				sfWindow_setFramerateLimit(window, 24);
			break;
			case sfEvtKeyPressed:
				// TODO: capture keyboard keys
				g_isWindowOpen = !sfKeyboard_isKeyPressed(sfKeyEscape);
				
			break;
			case sfEvtKeyReleased:
				// TODO: capture keyboard keys
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	// variables
	sfVideoMode videoMode = { SCREEN_WIDTH, SCREEN_HEIGHT, 32 };
	sfContextSettings contextSettings = { 0, 0, 0, 2, 1 };
	sfWindow* window = sfWindow_create( videoMode, "CSoftwareRasterizer JJoosten", sfDefaultStyle, &contextSettings);

	int glewSuccesInit = glewInit();

	bool openGLInit = OGL_Init( SCREEN_WIDTH, SCREEN_HEIGHT);

	Renderer* renderer = Renderer_Create( SCREEN_WIDTH, SCREEN_HEIGHT);
	
	Game* game = Game_Create();

	Stopwatch stopwatch = Stopwatch_Init();
	
	OGLSurface* surface = OGLSurface_Create( renderer->FrameBuffer);

	// setup buffers
	OGLSurface_MapToFrameBuffer( surface, renderer->FrameBuffer);

	// start stopwatch for first frametime of < ammount
	Stopwatch_Start( &stopwatch);
	
	// game loop
	while( g_isWindowOpen)
	{
		// variables
		double deltaTimeSec = 0;
	
		FrameBuffer_ClearToBlack( renderer->FrameBuffer);
	
		// setup timers
		Stopwatch_Stop( &stopwatch);
		Stopwatch_Start( &stopwatch);
		deltaTimeSec = Stopwatch_GetIntervalInSeconds( &stopwatch);

		handleWindowEvents( window);

		Game_Update( game, deltaTimeSec);

		Game_Render( game, renderer, deltaTimeSec);
		
		OGLSurface_Draw( surface);
		OGLSurface_MapToFrameBuffer( surface, renderer->FrameBuffer);

		sfWindow_display( window);
	}
	
	Game_Destroy( game);
	OGLSurface_Destroy( surface);
	Renderer_Destroy( renderer);
	sfWindow_destroy(window);
	
	return 0;
}