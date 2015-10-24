#ifndef CSR_WINDOWS_H
#define CSR_WINDOWS_H

#include "../Defines.h"
#include "../Typedefs.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"

#define CSR_MAX_WINDOW_NAME_LENGTH 255

#ifndef CSR_ENABLE_MULTISAMPLING
#define CSR_ENABLE_MULTISAMPLING TRUE
#endif 

#ifndef CSR_ENABLE_VSYNC
#define CSR_ENABLE_VSYNC TRUE
#endif 

typedef struct
{
	unsigned int Width;
	unsigned int Height;
	unsigned int X;
	unsigned int Y;
	char Title[CSR_MAX_WINDOW_NAME_LENGTH];
	Keyboard* Keyboard;
	Mouse* Mouse;
	bool HasFocus;
} Window;

Window* Window_Create(unsigned int x, unsigned int y, unsigned int width, unsigned int height, const char* const defaultName);
void Window_Destroy(Window* const window);
void Window_SetKeyboard(Window* const window, Keyboard* const keyboard);
void Window_SetMouse(Window* const window, Mouse* const mouse);
bool Window_HandleMessages(Window* const window);
void Window_SwapBuffer(Window* const window);
void Window_SetTitle(Window* const window, const char* const title);
void Window_SetVSync(Window* const window, bool isVSyncEnabled);
bool Window_HasFocus(Window* const window);


#endif // WINDOWS_H