#include "Mouse.h"
#include <assert.h>
#include <string.h>

void Mouse_Initialize( Mouse* const mouse)
{
	assert( mouse && "mouse is NULL");
	memset( &mouse->CurrentState, 0, sizeof(MouseState));
	memset( &mouse->PrevState, 0, sizeof(MouseState));
}

void Mouse_SetKeyDown( Mouse* const mouse, MouseButtons mouseButton)
{
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 8 && "Button is out of range \n");
	
	mouse->PrevState = mouse->CurrentState;
	mouse->CurrentState.State |= mouseButton;
}

void Mouse_SetKeyUp( Mouse* const mouse, MouseButtons mouseButton)
{
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 8 && "Button is out of range \n");
	
	mouse->PrevState = mouse->CurrentState;
	mouse->CurrentState.State = (mouse->CurrentState.State & (~mouseButton));
}

void Mouse_SetScreenPos( Mouse* const mouse, unsigned short screenPosX, unsigned short screenPosY)
{
	assert( mouse && "mouse is NULL");
	
	mouse->PrevState = mouse->CurrentState;
	mouse->CurrentState.MousePosX = screenPosX;
	mouse->CurrentState.MousePosY = screenPosY;
}

bool Mouse_IsKeyDown( Mouse* const mouse, MouseButtons mouseButton)
{
	int isolatedKeyFlag = 0;
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 8 && "Button is out of range \n");
	
	isolatedKeyFlag = mouse->CurrentState.State & mouseButton;
	return (bool)(isolatedKeyFlag >> (isolatedKeyFlag >> 1));
}

bool Mouse_IsKeyUp( Mouse* const mouse, MouseButtons mouseButton)
{
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 8 && "Button is out of range \n");
	
	return !Mouse_IsKeyDown( mouse, mouseButton);
}

bool Mouse_IsKeyPressed( Mouse* const mouse, MouseButtons mouseButton)
{
	int isolatedKeyFlag = 0;
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 8 && "Button is out of range \n");
	
	isolatedKeyFlag = mouse->PrevState.State & mouseButton;
	return (bool)(isolatedKeyFlag >> (isolatedKeyFlag >> 1));
}

short Mouse_GetScreenPosX( Mouse* const mouse)
{
	assert( mouse && "mouse is NULL");
	return mouse->CurrentState.MousePosX;
}

short Mouse_GetScreenPosY( Mouse* const mouse)
{
	assert( mouse && "mouse is NULL");
	return mouse->CurrentState.MousePosY;
}

MouseState Mouse_GetCurrentMouseState( Mouse* const mouse)
{
	assert( mouse && "mouse is NULL");
	return mouse->CurrentState;
}

MouseState Mouse_GetPrevMouseState( Mouse* const mouse)
{
	assert( mouse && "mouse is NULL");
	return mouse->PrevState;
}
