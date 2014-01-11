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

	bool openGLInit = OGLInit( SCREEN_WIDTH, SCREEN_HEIGHT);

	Renderer* renderer = RendererCreate( SCREEN_WIDTH, SCREEN_HEIGHT);
	
	Game game = GameCreate();

	Stopwatch stopwatch = StopwatchCreate();
	
	OGLSurface surface = OGLSurfaceCreate( renderer->FrameBuffer);

	// setup buffers
	OGLSurfaceMapToFrameBuffer( &surface, renderer->FrameBuffer);

	// start stopwatch for first frametime of < ammount
	StopwatchStart( &stopwatch);
	
	// game loop
	while( g_isWindowOpen)
	{
		// variables
		double deltaTimeSec = 0;
	
		FrameBufferClear( renderer->FrameBuffer, 0xFF0000FF);
	
		// setup timers
		StopwatchStop( &stopwatch);
		StopwatchStart( &stopwatch);
		deltaTimeSec = StopwatchGetIntervalInSeconds( &stopwatch);

		handleWindowEvents( window);

		GameUpdate( &game, deltaTimeSec);

		GameRender( &game, deltaTimeSec);
		
		OGLSurfaceDraw( &surface);
		OGLSurfaceMapToFrameBuffer( &surface, renderer->FrameBuffer);

		sfWindow_display( window);
	}
	
	StopwatchDestroy( &stopwatch);
	GameDestroy( &game);
	OGLSurfaceDestroy( &surface);
	RendererDestroy( renderer);
	sfWindow_destroy(window);
	
	return 0;
}