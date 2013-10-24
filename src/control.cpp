/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/
#include "include/control.h"

Controller::Controller()
{
	mode = INSERT;
}

void Controller::ParseSearch(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	switch (ch)
	{
		case 0:
		break;
		default:;
	}
}

void Controller::ParseReplace(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	switch (ch)
	{
		case 0:
		break;
		default:;
	}
}

void Controller::ParseInsert(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	uint8_t txt = 0;
	//uint8_t* txtptr = &txt;
	switch (ch)
	{
		case ' ' ... '~': 
		txt=(uint8_t) ch;
		buffers[current_buffer]->Insert(&txt);	
		break;
		case 0x8: buffers[current_buffer]->Delete(-1);
		break;
		default:;
	}
}

void Controller::ParseView(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	switch (ch)
	{
		case 0:
		break;
		default:;
	}
}

void Controller::SetRunning(bool* Running)
{
	running = Running;
}

void Controller::Control(vector<Buffer*> buffers, uint8_t current_buffer)
{
	int32_t ch = getch(); //get the current character
	if(ch == 0x1B) *running = false; //running = false; //if we get q then stop the program
	switch (mode) //check what mode we are in
	{
		case SEARCH: ParseSearch(ch, buffers, current_buffer);
		break;

		case REPLACE: ParseReplace(ch, buffers, current_buffer);
		break;

		case INSERT: ParseInsert(ch, buffers, current_buffer);
		break;

		case VIEW: ParseView(ch, buffers, current_buffer);
		break;
		default:;
	}
	DrawScreen(buffers, current_buffer); //Draw the Screen
}
