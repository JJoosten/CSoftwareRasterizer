#ifndef CSR_GAME_H
#define CSR_GAME_H

#include "Defines.h"
#include "Texture/Texture.h"
#include "VertexData/Mesh.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

typedef struct
{
	Camera* Camera;
	Texture* DiffuseTexture;
	Mesh* CubeModel;
	Keyboard* Keyboard;
	Mouse* Mouse;
} Game;

Game* Game_Create( Keyboard* const keyboard, Mouse* const mouse);
void Game_Destroy( Game* const game);
void Game_Update( Game* const game, const double deltaTimeSec);
void Game_Render( Game* const game, Renderer* const renderer, const double deltaTimeSec);

#endif // GAME_H