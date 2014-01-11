
#include "Settings.h"
#include "Game.h"
#include "Renderer/Renderer.h"
#include "Stopwatch/Stopwatch.h"

int main( void)
{
	// variables
	int i = 0;
	

	// TODO: create window
	
	Renderer* renderer = RendererCreate( SCREEN_WIDTH, SCREEN_HEIGHT);
	
	Game game = GameCreate();

	Stopwatch stopwatch = StopwatchCreate();
	StopwatchStart( &stopwatch);

	// game loop
	while(true)
	{
		// variables
		double deltaTimeSec = 0;

		StopwatchStop( &stopwatch);
		StopwatchStart( &stopwatch);
		deltaTimeSec = StopwatchGetIntervalInSeconds( &stopwatch);

		GameUpdate( &game, deltaTimeSec);

		GameRender( &game, deltaTimeSec);

		RendererFlipBuffer( renderer);
		
		// TODO: display frame
	}

	GameDestroy( &game);
	RendererDestroy( renderer);
	
	StopwatchDestroy( &stopwatch);
	return 0;
}