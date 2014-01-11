#ifndef CSR_GAME_H
#define CSR_GAME_H

#include "Defines.h"
#include "Texture/Texture.h"

#define Game struct sGame

Game
{
	Texture* DiffuseTexture;
};

Game GameCreate( void);
void GameDestroy( Game* game);
void GameUpdate( Game* game, const double deltaTimeSec);
void GameRender( Game* game, const double deltaTimeSec);

#endif // GAME_H