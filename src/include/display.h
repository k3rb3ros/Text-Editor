#ifndef DISPLAY_H
#define DISPLAY_H

#include "buffer.h"
#include "includes.h"

#define CONSOLE_HEIGHT 24
#define CONSOLE_WIDTH 80

class Window
{
	private:
	public:
	Window(); //default Constructor
	void NcursesTest(); //Test ncurses
	void DrawScreen(vector<Buffer> world, uint8_t current_buffer);
	~Window(); //Destructor
};

#endif
