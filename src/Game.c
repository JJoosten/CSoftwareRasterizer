#include "Game.h"
#include "Settings.h"
#include "Math/Mat4.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Game* Game_Create( Keyboard* const keyboard)
{
	Mat4 tmpProjectionMatrix;
	
	Game* game = malloc( sizeof(Game));
	
	memset( game, 0, sizeof(Game));

	game->Keyboard = keyboard;

	game->DiffuseTexture = Texture_Load("assets/textures/checkerboard.png");
	
	Mat4_LoadPerspective( &tmpProjectionMatrix, 70.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
	game->Camera = Camera_Create( &tmpProjectionMatrix);

	return game;
}


void Game_Destroy( Game* const game)
{
	printf("Game_Destroy \n");

	Camera_Destroy( game->Camera);
}


void Game_Update( Game* const game, const double deltaTimeSec)
{
	printf("Game_Update %f \n", deltaTimeSec);

}

void Game_Render( Game* const game, Renderer* const renderer, const double deltaTimeSec)
{	
	unsigned int y = 0;

	// clear frame to black
	FrameBuffer_ClearToBlack( renderer->FrameBuffer);
		
	// copy the test texture into the frame buffer
	for( y; y < game->DiffuseTexture->Height; ++y)
	{
		unsigned int x = 0;
		for( x; x < game->DiffuseTexture->Width; ++x)
		{
			renderer->FrameBuffer->Pixels[y * renderer->FrameBuffer->Width + x] =  game->DiffuseTexture->Texels[y * game->DiffuseTexture->Width + x];
		}
	}

	printf("Game_Render %f \n", deltaTimeSec);

}