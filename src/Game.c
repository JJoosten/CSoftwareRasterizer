#include "Game.h"
#include <stdio.h>
#include <string.h>


Game GameCreate( void)
{
	Game game;
	memset(&game, 0, sizeof(Game));

	game.DiffuseTexture = TextureLoad("assets/textures/checkerboard.png");

	return game;
}


void GameDestroy( Game* game)
{
	printf("GameDestroy \n");

}


void GameUpdate( Game* game, const double deltaTimeSec)
{
	printf("GameUpdate \n");

}

void GameRender( Game* game, const double deltaTimeSec)
{	
	printf("GameRender \n");

}