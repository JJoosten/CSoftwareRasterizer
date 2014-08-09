#ifndef CSR_MOUSE_H
#define CSR_MOUSE_H

#include "../Defines.h"
#include "../Typedefs.h"
#include "MouseButtons.h"

typedef struct
{
	unsigned char State;
	unsigned char _padding[3];
	unsigned short MousePosX;
	unsigned short MousePosY;
} MouseState;

typedef struct
{
	MouseState CurrentState;
	MouseState PrevState;
} Mouse;

void Mouse_Initialize( Mouse* const mouse);

void Mouse_SetKeyDown( Mouse* const mouse, MouseButtons mouseButton);
void Mouse_SetKeyUp( Mouse* const mouse, MouseButtons mouseButton);
void Mouse_SetScreenPos( Mouse* const mouse, unsigned short screenPosX, unsigned short screenPosY);

bool Mouse_IsKeyDown( Mouse* const mouse, MouseButtons mouseButton);
bool Mouse_IsKeyUp( Mouse* const mouse, MouseButtons mouseButton); 
bool Mouse_IsKeyPressed( Mouse* const mouse, MouseButtons mouseButton);

short Mouse_GetScreenPosX( Mouse* const mouse);
short Mouse_GetScreenPosY( Mouse* const mouse);

MouseState Mouse_GetCurrentMouseState( Mouse* const mouse);
MouseState Mouse_GetPrevMouseState( Mouse* const mouse);
#endif