#ifndef DISPLAY_H
#define DISPLAY_H

#include "buffer.h"
#include "includes.h"

#define CONSOLE_HEIGHT 24
#define CONSOLE_WIDTH 80

class Window
{
	private:
	char* GetStatus();
	public:
	Window(); //default Constructor
	void DrawScreen(vector<Buffer> world, uint8_t current_buffer);
	void FreeWindow();
	void InitWindow();
	void NcursesTest(); //Test ncurses
	~Window(); //Destructor
};

#endif
