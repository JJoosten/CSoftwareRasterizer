#ifndef CSR_MOUSE_KEYS_H
#define CSR_MOUSE_KEYS_H

#include <SFML/Window.h>

typedef enum
{
	csrButtonNone = 0,
	csrButtonLeft = sfMouseLeft,
	csrButtonMiddle = sfMouseMiddle,
	csrButtonRight = sfMouseRight
} MouseButtons;

#endif