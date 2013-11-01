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
		case 18:
		mode = REPLACE;
		break;
		case 9:
		mode = INSERT;
		break;
		case 27:
		mode = VIEW;
		break;
		default:;
	}
}

void Controller::ParseReplace(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	switch (ch)
	{
		case 6:
		mode = SEARCH;
		break;
		case 9:
		mode = INSERT;
		break;
		case 27:
		mode = VIEW;
		break;
		default:;
	}
}

void Controller::ParseInsert(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	uint8_t txt = 0;
	switch (ch)
	{
		case 6:
		mode = SEARCH;
		break;
		case 27:
		mode = VIEW;
		break;
		case 18:
		mode = REPLACE;
		break;
		case ' ' ... '~': //Regular ascii range press
		txt=(uint8_t) ch;
		buffers[current_buffer]->Insert(&txt, 1);
		AdvanceCursor();	
		break;
		case 10: //Enter key Press
		buffers[current_buffer]->Insert(&txt, 1);
		WriteStatus(&txt, mode, ch, 6, 9);
		EndLine();
		break;
		case 263: //Backspace Press
                if(buffers[current_buffer]->GetPoint() > 0)
		{
			buffers[current_buffer]->Delete(-1);
			RetractCursor();
		}
		break;
		case 258: //Down arrow press
		EndLine();
		break;
		case 259: //Up arrow press
		UpLine();
		break;
		case 260: //Left arrow press 
                buffers[current_buffer]->SetPointR(-1);
		RetractCursor();
		break;
		case 261: //Right arrow press
		buffers[current_buffer]->SetPointR(1);
		AdvanceCursor();
		break;
		case 330: //Delete key press
		buffers[current_buffer]->Delete(1);
		default:;
	}
}

void Controller::ParseView(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	switch (ch)
	{
		case 6:
		mode = SEARCH;
		break;
		case 9:
		mode = INSERT;
		break;
		case 18:
		mode = REPLACE;
		break;
		default:;
	}
}

void Controller::Welcome(int32_t &ch)
{
 curs_set(0); //Turn off the cursor
 //Display Welcome Message
 printw("                       Kedit By K3rb3ros\n");
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
 printw("                 Press any key to continue\n");
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
	if(ch == 268) *running = false; //running = false; //if we get q then stop the program
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
	WriteStatus(NULL, mode, ch, buffers[current_buffer]->GetLineNumber(), buffers[current_buffer]->GetTextLength());
        ch = getch(); //get the current character
}
