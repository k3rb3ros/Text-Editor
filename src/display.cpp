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

void Window::ClearLine(uint8_t* current_line, uint16_t len)
{
	for(uint16_t i=0; i<len; i++) current_line[i] = 0;
}

void Window::WriteSearch(uint8_t* search)
{
	uint8_t* zed = (uint8_t*)calloc(CONSOLE_WIDTH, sizeof(uint8_t));
	uint32_t y = 0;
	uint32_t x = 0;

	getyx(stdscr, y, x); //Get the cursor position
	mvprintw(CONSOLE_HEIGHT, 0, "%s", zed); //zero out anything on that line
	mvprintw(CONSOLE_HEIGHT, 0, "SEARCH: %s", search); //write the status
	move(y, x); //restore the cursor position
	refresh();
	free(zed); //free the memory we allocated
}

void Window::WriteStatus(uint8_t* status, uint32_t mode, int32_t ch, uint32_t line_num, uint32_t column_num) //Print the status line
{
	uint8_t Mode[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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
			default: ClearLine(Mode, 14);
		}
		getyx(stdscr, y, x); //Save the current location of the cursor
		if(status != NULL)
		{
			mvprintw(CONSOLE_HEIGHT, 0, "%s %s, char(%d) COL:%u LINE:%u",status, Mode, ch, line_num, column_num);
		}	
		else mvprintw(CONSOLE_HEIGHT, 0, "%s char(%d) COL:%u LINE:%u", Mode, ch, line_num, column_num);
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

bool Window::AdvanceCursor(Buffer* buffer, bool check) //Advance the cursor to the right if there is text there
{
 	uint32_t x = 0;
 	uint32_t y = 0;
 	getyx(stdscr, y, x);
	if(check && !(buffer -> BoundRight())) return false; //if check is on only continue if the cursor is still in the text
	else
	{
		if((buffer -> CheckRight() || x >= CONSOLE_WIDTH-1) && y < CONSOLE_HEIGHT-1) move(++y, 0);
 		else if(x < CONSOLE_WIDTH) move(y, ++x);
		else return false; //Scroll FIXME
		return true;
	}
}

void Window::DeclinateCursor(Buffer* buffer) //move the cursor down if we can
{
	int32_t x = 0;
	int32_t y = 0;
	getyx(stdscr, y, x);
	x = buffer->LookForward(x);
	if(x >=0 && y < CONSOLE_HEIGHT-1) move(y+1, x); 
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
			ClearLine(window_buffer, (CONSOLE_WIDTH*CONSOLE_HEIGHT)+1); //clearn anything in the line buffer
			GetWindow(buffers, current_buffer, window_buffer, index, length_of_text); //get the line and update any values as needed
			mvprintw(0, 0, (char*) window_buffer);//(char*)current_line); //print the current line
		}
		move(y, x); //return the cursor location where it was
		refresh(); //Print the screen
	}
}

void Window::EndLine() //move the cursor down to the start of the next line
{
	uint32_t y = 0;
	uint32_t x = 0;
	getyx(stdscr, y, x);
	if(y < CONSOLE_HEIGHT) y++;
           //scroll buffer down FIXME
        move(y, 0);
}

void Window::InclinateCursor(Buffer* buffer)
{
	int32_t x = 0;
	int32_t y = 0;
	getyx(stdscr, y, x);
	x = buffer -> LookBackward(x);
	if(x >= 0 && y > 0) move(y-1, x);
	//else true; //sroll up or do nothing FIXME 
}

void Window::MoveToSearch(Buffer* buffer, uint16_t initial, uint16_t _new)
{
	uint16_t y = buffer -> GetNewY(initial, _new);
	uint16_t x = buffer -> GetNewX(initial, _new);

	move(y, x); //move the cursor to position of the point
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

void Window::RetractCursor(Buffer* buffer, bool check)
{
	int32_t y = 0;
	int32_t x = 0;

	getyx(stdscr, y, x);
	if(x > 0) move(y, --x);
	//case of x = 0, not necessarily EOL
	else if(check && y > 0) move(--y, buffer -> LookLeft()); //move the cursor to the end of the previous line
}

Window::~Window()
{
	echo();
	nocbreak();
	endwin();
	keypad(stdscr, FALSE);
}
