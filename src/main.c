#include <GL/glew.h>
#include "Platform/Platform.h"
#include "Typedefs.h"
#include "Settings.h"
#include "Game.h"
#include "Renderer/Renderer.h"
#include "OpenGL/OGLSurface.h"
#include "Stopwatch/Stopwatch.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

// global variables
bool g_isWindowOpen = true;

int main(int argc, char *argv[])
{
	Window* window = Window_Create(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, "CSoftwareRasterizer JJoosten");
	
	bool openGLInit = OGL_Init( SCREEN_WIDTH, SCREEN_HEIGHT);

	Renderer* renderer = Renderer_Create( SCREEN_WIDTH, SCREEN_HEIGHT);
	
	Keyboard keyboard;
	Mouse mouse;

	Game* game = Game_Create( &keyboard, &mouse);
	
	OGLSurface* surface = OGLSurface_Create( renderer->FrameBuffer);

	Stopwatch stopwatch;

	Stopwatch_Init( &stopwatch);

	// set input to window
	Window_SetKeyboard(window, &keyboard);
	Window_SetMouse(window, &mouse);

	// setup buffers
	OGLSurface_MapToFrameBuffer( surface, renderer->FrameBuffer);

	// start stopwatch for first frametime of < ammount
	Stopwatch_Start( &stopwatch);
	
	// game loop
	while( g_isWindowOpen)
	{
		// variables
		double deltaTimeSec = 0;
	
		// setup timers
		Stopwatch_Stop( &stopwatch);
		Stopwatch_Start( &stopwatch);
		deltaTimeSec = Stopwatch_GetIntervalInSeconds( &stopwatch);

		// update input
		Keyboard_Update( &keyboard);

		g_isWindowOpen = Window_HandleMessages(window);

		Game_Update( game, deltaTimeSec);

		Game_Render( game, renderer, deltaTimeSec);
		
		OGLSurface_Draw( surface);
		OGLSurface_MapToFrameBuffer( surface, renderer->FrameBuffer);

		Window_SwapBuffer( window);

		CHECK_OGL_ERROR_IN_DEBUG;

		g_isWindowOpen = !Keyboard_IsKeyPressed( &keyboard, csrKeyEscape);
	}
	
	OGLSurface_Destroy(surface);
	Game_Destroy(game);
	Renderer_Destroy( renderer);
	Window_Destroy( window);
	
	return 0;
}