#include "include/incremental_redisplay.h"

Window::Window()
{
}

void Window::NcursesTest()
{
	initscr();
	printw("Hello World !!");
	refresh();
	getch();
	endwin();
}

Window::~Window()
{
}
