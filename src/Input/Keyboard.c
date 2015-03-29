#include "Keyboard.h"
#include <string.h>
#include <assert.h>

void Keyboard_Initialize( Keyboard* const keyboard)
{
	assert( keyboard && "keyboard is NULL");
	memset( keyboard->CurrentKeysDown, 0, sizeof(bool) * CSR_KEYBOARD_MAX_KEYS);
	memset( keyboard->PreviousKeysDown, 0, sizeof(bool) * CSR_KEYBOARD_MAX_KEYS);
}

void Keyboard_SetKeyDown( Keyboard* const keyboard, const int key)
{
	assert( keyboard && "keyboard is NULL");
	assert( key >= 0 && key < CSR_KEYBOARD_MAX_KEYS && "Key is out of range \n");
	keyboard->CurrentKeysDown[key] = true;
}

void Keyboard_SetKeyUp( Keyboard* const keyboard, const int key)
{
	assert( keyboard && "keyboard is NULL");
	assert( key >= 0 && key < CSR_KEYBOARD_MAX_KEYS && "Key is out of range \n");
	keyboard->CurrentKeysDown[key] = false;
}

bool Keyboard_IsKeyDown( Keyboard* const keyboard, const int key)
{
	assert( keyboard && "keyboard is NULL");
	assert( key >= 0 && key < CSR_KEYBOARD_MAX_KEYS && "Key is out of range \n");
	return keyboard->CurrentKeysDown[key] == true ? true : false;
}

bool Keyboard_IsKeyUp( Keyboard* const keyboard, const int key)
{
	assert( keyboard && "keyboard is NULL");
	assert( key >= 0 && key < CSR_KEYBOARD_MAX_KEYS && "Key is out of range \n");
	return keyboard->CurrentKeysDown[key] == false ? true : false;
}

bool Keyboard_IsAnyKeyDown( Keyboard* const keyboard)
{
	int i = 0;
	assert( keyboard && "keyboard is NULL");
	for( i = 0; i < CSR_KEYBOARD_MAX_KEYS; ++i)
	{
		if( keyboard->CurrentKeysDown[i] == true)
			return true;
	}

	return false;
}

bool Keyboard_IsKeyPressed( Keyboard* const keyboard, const int key)
{
	bool currentKeyDown = false;
	bool prevKeyDown = false;
	
	assert( keyboard && "keyboard is NULL");
	assert( key > 0 && key < CSR_KEYBOARD_MAX_KEYS && "Key is out of range \n");

	currentKeyDown = keyboard->CurrentKeysDown[key];
	prevKeyDown = keyboard->PreviousKeysDown[key];
	
	return (currentKeyDown == false && prevKeyDown == true) ? true : false;
}

bool Keyboard_IsAnyKeyPressed( Keyboard* const keyboard)
{
	int i = 0;
	assert( keyboard && "keyboard is NULL");
	for( i = 0; i < CSR_KEYBOARD_MAX_KEYS; ++i)
	{
		if( Keyboard_IsKeyPressed(keyboard, i) == true)
			return true;
	}

	return false;
}

void Keyboard_Update( Keyboard* const keyboard)
{
	assert( keyboard && "keyboard is NULL");
	memcpy( keyboard->PreviousKeysDown, keyboard->CurrentKeysDown, sizeof(bool) * CSR_KEYBOARD_MAX_KEYS);
}