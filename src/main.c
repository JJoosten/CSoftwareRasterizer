#include <GL/glew.h>
#include "Typedefs.h"
#include "Settings.h"
#include "Game.h"
#include "Renderer/Renderer.h"
#include "OpenGL/OGLSurface.h"
#include "Stopwatch/Stopwatch.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include <SFML/Window.h>

// global variables
bool g_isWindowOpen = true;


void handleWindowEvents( sfWindow* window, Keyboard* keyboard, Mouse* mouse)
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
			case sfEvtMouseButtonPressed:
			{
				unsigned int key = 1 * sfMouse_isButtonPressed(sfMouseLeft);
				key |= 2 * sfMouse_isButtonPressed(sfMouseMiddle);
				key |= 4 * sfMouse_isButtonPressed(sfMouseRight);
				Mouse_SetKeyDown(mouse, key);
			}
			break;
			case sfEvtMouseButtonReleased:
			{
				unsigned int key = 1 * (!sfMouse_isButtonPressed(sfMouseLeft));
				key |= 2 * (!sfMouse_isButtonPressed(sfMouseMiddle));
				key |= 4 * (!sfMouse_isButtonPressed(sfMouseRight));
				Mouse_SetKeyUp(mouse, key);
			}
			break;
			case sfEvtMouseMoved:
			{
				sfVector2i pos = sfMouse_getPosition(NULL);
				Mouse_SetScreenPos( mouse, pos.x, pos.y);
			}
			case sfEvtKeyPressed:
			{
				unsigned int i = 0; 
				for( i; i < CSR_KEYBOARD_MAX_KEYS; ++i)
				{
					if( sfKeyboard_isKeyPressed(i))
					{
						Keyboard_SetKeyDown(keyboard, i);
					}
				}
			}
			break;
			case sfEvtKeyReleased:
			{
				unsigned int i = 0; 
				for( i; i < CSR_KEYBOARD_MAX_KEYS; ++i)
				{
					if( !sfKeyboard_isKeyPressed(i))
					{
						Keyboard_SetKeyUp(keyboard, i);
					}
				}
			}
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
	
	Keyboard keyboard;
	Mouse mouse;

	Game* game = Game_Create( &keyboard, &mouse);
	
	OGLSurface* surface = OGLSurface_Create( renderer->FrameBuffer);

	Stopwatch stopwatch;

	Stopwatch_Init( &stopwatch);

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

		handleWindowEvents( window, &keyboard, &mouse);

		Game_Update( game, deltaTimeSec);

		Game_Render( game, renderer, deltaTimeSec);
		
		OGLSurface_Draw( surface);
		OGLSurface_MapToFrameBuffer( surface, renderer->FrameBuffer);

		sfWindow_display( window);

		g_isWindowOpen = !Keyboard_IsKeyPressed( &keyboard, csrKeyEscape);
	}
	
	Game_Destroy( game);
	OGLSurface_Destroy( surface);
	Renderer_Destroy( renderer);
	sfWindow_destroy(window);
	
	return 0;
}