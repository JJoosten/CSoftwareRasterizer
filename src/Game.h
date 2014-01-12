#ifndef CSR_GAME_H
#define CSR_GAME_H

#include "Defines.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"

typedef struct sGame
{
	Camera* Camera;
	Texture* DiffuseTexture;
} Game;

Game* Game_Create( void);
void Game_Destroy( Game* game);
void Game_Update( Game* game, const double deltaTimeSec);
void Game_Render( Game* game, Renderer* const renderer, const double deltaTimeSec);

#endif // GAME_H