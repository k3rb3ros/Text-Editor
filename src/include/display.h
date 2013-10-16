#ifndef DISPLAY_H
#define DISPLAY_H

#include "includes.h"

#define CONSOLE_HEIGHT 24
#define CONSOLE_WIDTH 80

class Window
{
	private:
	public:
	Window(); //default Constructor
	void NcursesTest(); //Test ncurses
	~Window(); //Destructor
};

#endif
