
#include "Settings.h"
#include "Game.h"
#include "Renderer/Renderer.h"

int main( void)
{
	// create window

	Renderer renderer = RendererCreate( SCREEN_WIDTH, SCREEN_HEIGHT);
	
	Game game = GameCreate();

	double deltaTimeSec = 0;

	// game loop
	while(true)
	{
		GameUpdate( &game, deltaTimeSec);

		GameRender( &game, deltaTimeSec);

		RendererFlipBuffer( &renderer);
		
		// TODO: display frame
	}

	GameDestroy( &game);

	return 0;
}