#include "include/display.h"

void Window::GetWindow(vector<Buffer*> &buffers, uint8_t &current_buffer, uint8_t* current_window, uint16_t &index, uint16_t &length_remaining)
{
	uint8_t ch = 0;
	uint16_t i = 0;
	if(buffers[current_buffer] == NULL)
	{
		cerr << "Buffer passed to get line is null" << endl;
		return;
	}
	while(length_remaining > 0)
	{
		ch = buffers[current_buffer]->GetCh(index++);
		if(ch != 0) current_window[i++] = ch;
		length_remaining --;
	}
}

void Window::ClearLine(uint8_t* current_line)
{
 	uint32_t len = strlen((char*)current_line);
	for(uint8_t i=0; i<len+1; i++) current_line[i] = 0;
}

void Window::WriteStatus(uint8_t* status, uint32_t mode, int32_t ch, uint32_t line_num, uint32_t column_num) //Print the status line
{
	uint8_t Mode[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint32_t len = 0;
	uint32_t y = 0;
	uint32_t x = 0;

	if(mode != WELCOME) //if not in Welcome mode turn on the status line
	{	
		switch (mode)
		{
			case SEARCH: strncpy((char*)Mode, "-- SEARCH --", 12); 
			break;
			case REPLACE: strncpy((char*)Mode, "-- REPLACE --", 13); 
			break;
			case INSERT: strncpy((char*)Mode,"-- INSERT --", 12); 
			break;
			default: ClearLine(Mode);
		}
		getyx(stdscr, y, x); //Save the current location of the cursor
		if(status != NULL)
		{
			len = strlen((char*)status); 
			mvprintw(CONSOLE_HEIGHT, 0, "%s %s, char(%d) %u:%u",status, Mode, ch, line_num, column_num);
		}	
		else mvprintw(CONSOLE_HEIGHT, 0, "%s char(%d) %u:%u", Mode, ch, line_num, column_num);
		move(y, x); //Restor the cursors original location
		refresh();
	}
}

Window::Window()
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
}

void Window::AdvanceCursor()
{
 uint32_t x = 0;
 uint32_t y = 0;
 getyx(stdscr, y, x);
 if(x < CONSOLE_WIDTH) move(y, x+1);
 else if(x >= CONSOLE_WIDTH && y < CONSOLE_HEIGHT) move(y+1, 0);
}

void Window::DrawScreen(vector<Buffer*> &buffers, uint8_t &current_buffer)
{
	uint8_t window_buffer[(CONSOLE_WIDTH*CONSOLE_HEIGHT)+1];
	uint16_t index = 0;
	uint16_t length_of_text = buffers[current_buffer]->GetTextLength();
	uint32_t x = 0;
	uint32_t y = 0;
	
	if(buffers.size() > 1)
	{
		//logic for drawing screen from two buffers goes here
	}
	else //single buffer mode
	{
		getyx(stdscr, y, x); //save the cursor location
		clear(); //Clear anything on the screen
		while(length_of_text != 0)
		{
			ClearLine(window_buffer); //clearn anything in the line buffer
			GetWindow(buffers, current_buffer, window_buffer, index, length_of_text); //get the line and update any values as needed
			mvprintw(0, 0, (char*) window_buffer);//(char*)current_line); //print the current line
		}
		move(y, x); //return the cursor location where it was
		refresh(); //Print the screen
	}
}

void Window::EndLine()
{
	uint32_t y = 0;
	uint32_t x = 0;
	getyx(stdscr, y, x);
	if(y < CONSOLE_HEIGHT) move(++y, 0);
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

void Window::RetractCursor()
{
	uint32_t y = 0;
	uint32_t x = 0;
	getyx(stdscr, y, x);
	if(x > 0) move(y,--x);
	else if(y > 0) move(--y, 0);
}

Window::~Window()
{
	echo();
	nocbreak();
	endwin();
	keypad(stdscr, FALSE);
}
