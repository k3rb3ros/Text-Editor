#include "include/display.h"

void Window::GetLine(vector<Buffer*> &buffers, uint8_t &current_buffer, uint8_t* current_line, uint16_t &index, uint16_t &length_remaining, uint8_t &line_number)
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
		current_line[i++] = ch;
		length_remaining --;
		if(ch == '\n') 
		{
			line_number ++;
			break;
		}
	}
}

/*void Window::GetStatus(uint8_t* status)
{
	if(file_name != NULL) 
	{
		sprintf(status, "%s Line:%u, Character:%u", file_name, 0, 69);
	}
	else
	{
		sprintf(status, " Line:%u, Character:%u", 0, 69);
	}	
	return status;
}*/

void Window::ClearLine(uint8_t* current_line)
{
	for(uint8_t i=0; i<CONSOLE_WIDTH+1; i++) current_line[i] = 0;
}

Window::Window()
{
	initscr();
	noecho();
	cbreak();
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
	uint8_t current_line[CONSOLE_WIDTH+1];
	uint8_t line_number = 0;
	uint16_t index = 0;
	uint16_t length_of_text = buffers[current_buffer]->GetTextLength();
	uint32_t i = 0;
	uint32_t x = 0;
	uint32_t y = 0;
	
	if(buffers.size() > 1)
	{
		//logic for drawing screen from two buffers goes here
	}
	else //single buffer mode
	{
		getyx(stdscr, y, x); //save the cursor location
		move(0,0); //set the cursor to the top left of the screen
		while(length_of_text != 0)
		{
			ClearLine(current_line); //clearn anything in the line buffer
			move(line_number, 0); //move the cursor to the line we are printing
			GetLine(buffers, current_buffer, current_line, index, length_of_text, line_number); //get the line and update any values as needed
			printw((char*) current_line);//(char*)current_line); //print the current line
		}
		move(CONSOLE_HEIGHT, 0); //move the the Status line (Line 25)
		ClearLine(current_line); //clearn anything in the line buffer
		printw("Status line"); 
		move(y, x); //return the cursor location where it was
		refresh(); //Print the screen
		//getch(); //Wait for user input temporary until moved to command loop
	}
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
	echo();
	nocbreak();
	endwin();
}
