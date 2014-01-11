#include "Game.h"
#include <stdio.h>
#include <string.h>


Game GameCreate( void)
{
	Game game;
	memset(&game, 0, sizeof(Game));

	game.DiffuseTexture = TextureLoad("assets/textures/checkerboard.png");

	game.Camera = CameraCreate();

	return game;
}


void GameDestroy( Game* game)
{
	printf("GameDestroy \n");

	CameraDestroy( &game->Camera);
}


void GameUpdate( Game* game, const double deltaTimeSec)
{
	printf("GameUpdate %f \n", deltaTimeSec);

}

void GameRender( Game* game, const double deltaTimeSec)
{	
	printf("GameRender %f \n", deltaTimeSec);

}