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
 printw("                  -so/-                 .-          \n");
 printw("                 os-..:syo++o/+/o+++/oysd++/        \n");
 printw("                -d......./y/-.-...:-//:m+:./y`      \n");
 printw("               `hd......ssmy/:oossdMmhoy/:...+`     \n");
 printw("               oMh..+y-.ohdhs+/..-.-o.+yyyy/.-o     \n");
 printw("               oMs.omo-..-....................:o    \n");
 printw("              /MN/./Nh/:.----..............-+mh+s   \n");
 printw("             sMMm+.-ydMmNMMMMm+:-::.....-sNshdMyd+  \n");
 printw("           `hMNo-..+mMMMo::ohhdmNNNy++hsNNmh+oymod` \n");
 printw("          `mMMh...:ymMMMhshhh--oysohs:++:--oh+yMooo \n");
 printw("          yMMMh/..-hMMMh/-+MMds::/:.......smy..--./o\n");
 printw("          hMMMNo.-smNM+....+mhsyh+.............../od\n");
 printw("          sMMMN+.--+Mm-..............o/:...o...../Ns\n");
 printw("          -MMMd+..yMMNs+-............+hy++o/-...+/-`\n");
 printw("          `MMMm/..:hMy/momo....-/....-dhNNy+.-.odm- \n");
 printw("           yMMdo...:+s-..oys...:mm+.....+s-.+o-NN-  \n");
 printw("           -MMN.-:..dMmy...:....-+yyo++++ho+:.om-   \n");
 printw("            oMMoho..yNMMmh::+-............../mm:    \n");
 printw("             yMMMhhs` :mMMNmNs+/.......-..sdNy`     \n");
 printw("              +NMMMM`   -yNMMMNy/...+:sNy/oN-       \n");
 printw("               `:omNy     `+dNNMm:dNNMMMmy:         \n");
 printw("                    +o        `/msmMNyo:            \n");
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
