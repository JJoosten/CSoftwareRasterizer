#ifndef CSR_KEYBOARD_H
#define CSR_KEYBOARD_H

#include "../Defines.h"
#include "../Typedefs.h"
#include "KeyboardKeys.h"

#define CSR_KEYBOARD_MAX_KEYS 256

typedef struct
{
	bool CurrentKeysDown[CSR_KEYBOARD_MAX_KEYS];
	bool PreviousKeysDown[CSR_KEYBOARD_MAX_KEYS];
} Keyboard;


void Keyboard_Initialize( Keyboard* const keyboard);

void Keyboard_SetKeyDown( Keyboard* const keyboard, const int key);
void Keyboard_SetKeyUp( Keyboard* const keyboard, const int key);

bool Keyboard_IsKeyDown( Keyboard* const keyboard, const int key);
bool Keyboard_IsKeyUp( Keyboard* const keyboard, const int key);
bool Keyboard_IsAnyKeyDown( Keyboard* const keyboard);

bool Keyboard_IsKeyPressed( Keyboard* const keyboard, const int key);
bool Keyboard_IsAnyKeyPressed( Keyboard* const keyboard);

void Keyboard_Update( Keyboard* const keyboard);

#endif //CSR_KEYBOARD_H