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
	assert( mouseButton >= 0 && mouseButton < 3 && "Button is out of range \n");

	mouse->CurrentState.State |= mouseButton;
}

void Mouse_SetKeyUp( Mouse* const mouse, MouseButtons mouseButton)
{
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 3 && "Button is out of range \n");
	
	mouse->CurrentState.State = (mouse->CurrentState.State & (~mouseButton));
}

void Mouse_SetScreenPosX( Mouse* const mouse, unsigned short screenPosX)
{
	assert( mouse && "mouse is NULL");

	mouse->CurrentState.MousePosX = screenPosX;
}

void Mouse_SetScreenPosY( Mouse* const mouse, unsigned short screenPosY)
{
	assert( mouse && "mouse is NULL");
	
	mouse->CurrentState.MousePosX = screenPosY;
}

bool Mouse_IsKeyDown( Mouse* const mouse, MouseButtons mouseButton)
{
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 3 && "Button is out of range \n");
	
	return (bool)(mouse->CurrentState.State &= mouseButton);
}

bool Mouse_IsKeyUp( Mouse* const mouse, MouseButtons mouseButton)
{
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 3 && "Button is out of range \n");
	
	return !Mouse_IsKeyDown( mouse, mouseButton);
}

bool Mouse_IsKeyPressed( Mouse* const mouse, MouseButtons mouseButton)
{
	assert( mouse && "mouse is NULL");
	assert( mouseButton >= 0 && mouseButton < 3 && "Button is out of range \n");
	
	return (bool)(mouse->PrevState.State &= mouseButton);
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

void Mouse_Update( Mouse* const mouse)
{
	assert( mouse && "mouse is NULL");
	
	mouse->PrevState = mouse->CurrentState;
	memset( &mouse->CurrentState, 0, sizeof(MouseState));
}