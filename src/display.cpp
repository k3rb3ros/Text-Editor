#include "include/display.h"

char* Window::GetStatus()
{
	char* status = new char[81];
	status[80] = 0;
	//if(file_name != NULL) 
	//{
		sprintf(status, " Line:%u, Character:%u", 0, 69);
	//}
	//else
	//{
	//	sprintf(status, " Line:%u, Character:%u", 0, 69);
	//}	
	return status;
}

Window::Window()
{
}

void Window::FreeWindow()
{
	endwin();
}

void Window::DrawScreen(vector<Buffer> world, uint8_t current_buffer)
{
	char line[81];
	//while(running == true)
	//{
	
		for(uint32_t i=0; i<25; i++)
		{
			move(i, 80);
			printw("$");	
		}
		move(25, 0);
		printw((char*)GetStatus());
		refresh();
		getch();
	//}
}

void Window::InitWindow()
{
	initscr();
}

void Window::NcursesTest()
{
	initscr();
	printw("Ncurses is working");
	move(25, 0);
	printw("Console line");
	refresh();
	getch();
	endwin();
}

Window::~Window()
{
}
