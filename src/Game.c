#include "Game.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Game* Game_Create( void)
{
	Game* game = malloc( sizeof(Game));
	memset( game, 0, sizeof(Game));

	game->DiffuseTexture = Texture_Load("assets/textures/checkerboard.png");

	game->Camera = Camera_Create();

	return game;
}


void Game_Destroy( Game* game)
{
	printf("Game_Destroy \n");

	Camera_Destroy( game->Camera);
}


void Game_Update( Game* game, const double deltaTimeSec)
{
	printf("Game_Update %f \n", deltaTimeSec);

}

void Game_Render( Game* game, const double deltaTimeSec)
{	
	printf("Game_Render %f \n", deltaTimeSec);

}