#ifndef CSR_GAME_H
#define CSR_GAME_H

#include "Defines.h"
#include "Texture/Texture.h"
#include "VertexData/Mesh.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Input/Keyboard.h"

typedef struct
{
	Camera* Camera;
	Texture* DiffuseTexture;
	Mesh* CubeModel;
	Keyboard* Keyboard;
} Game;

Game* Game_Create( Keyboard* const keyboard);
void Game_Destroy( Game* const game);
void Game_Update( Game* const game, const double deltaTimeSec);
void Game_Render( Game* const game, Renderer* const renderer, const double deltaTimeSec);

#endif // GAME_H