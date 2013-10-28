/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/
#include "include/control.h"

Controller::Controller()
{
	ch = 0;
	mode = WELCOME;
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
	uint8_t* txtptr = &txt;
	switch (ch)
	{
		case ' ' ... '~': //Regual ascii range press
		txt=(uint8_t) ch;
		buffers[current_buffer]->Insert(&txt, 1);
		AdvanceCursor();	
		break;
		case 10:
		buffers[current_buffer]->Insert(&txt, 1); //Enter key press
		EndLine();
		break;
		case 127: if(buffers[current_buffer]->GetPoint() > 0) //Backspace Press
		{
			buffers[current_buffer]->Delete(-1); 
			RetractCursor();
		}
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

void Controller::Welcome(int32_t &ch)
{
 curs_set(0); //Turn off the cursor
 //Display Welcome Message
 printw("                         Kedit By K3rb3ros\n");
 refresh();
 while(ch == 0) //Wait for user input
 {
  ch = getch(); 
 }
 clear();//clear the screen
 curs_set(1); //Turn on cursor
 mode = INSERT; //Enter insert mode
}

void Controller::SetRunning(bool* Running)
{
	running = Running;
}

void Controller::Control(vector<Buffer*> buffers, uint8_t current_buffer)
{
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

		case WELCOME: Welcome(ch);
		break;
		default:;
	}
	DrawScreen(buffers, current_buffer); //Draw the Screen
	WriteStatus(NULL, mode, ch, 3, 4);
        ch = getch(); //get the current character
}
