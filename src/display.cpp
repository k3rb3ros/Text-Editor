#include "include/display.h"

Window::Window()
{
}

void Window::NcursesTest()
{
	initscr();
	printw("Ncurses is working");
	refresh();
	getch();
	endwin();
}

Window::~Window()
{
}
