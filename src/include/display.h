#ifndef DISPLAY_H
#define DISPLAY_H

#include "buffer.h"
#include "includes.h"

#define CONSOLE_HEIGHT 23
#define CONSOLE_WIDTH 80

class Window
{
	private:
	void GetLine(vector<Buffer*> &buffers, uint8_t &current_buffer, uint8_t* current_line, uint16_t &index, uint16_t &length_remaining, uint8_t &line_number);

	//void GetLine(Buffer* current_buff, uint8_t* current_line, uint16_t &index, uint16_t &length_remaining, uint8_t &line_number);
	//void GetStatus(uint8_t* status, World* world);
	void ClearLine(uint8_t* current_line);

	public:
	Window(); //default Constructor
	void DrawScreen(vector<Buffer*> &buffers, uint8_t &current_buffer);
	void FreeWindow(); //Get Rid of me
	void InitWindow(); //Get Rid of me
	void NcursesTest(); //Test ncurses
	~Window(); //Destructor
};

#endif
