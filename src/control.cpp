/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/
#include "include/control.h"

Controller::Controller()
{
	ch = 0;
	display_status = false;
	mode = WELCOME;
	for(uint8_t i=0; i<=CONSOLE_WIDTH; i++) search_pattern[i] = 0;
}

void Controller::ClearBuff()
{
	for(uint8_t i=0; i<=CONSOLE_WIDTH; i++) search_pattern[i] = 0;
}

void Controller::DeletePtrn() //Delete a character from the search pattern
{
	uint16_t len = strlen((char*)search_pattern);
	if(len>0) search_pattern[len-1] = 0;
}

void Controller::InsertPtrn(uint8_t ch) //Insert the character passed in into search_pattern
{
	uint16_t len = strlen((char*)search_pattern);
	if(len < CONSOLE_WIDTH) search_pattern[len] = ch; 
}

void Controller::ParseSearch(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	uint8_t _ch = (uint8_t) ch;
	uint16_t old_point = 0;
	uint16_t new_point = 0;
	switch (ch)
	{
		case 9:
		mode = INSERT;
		break;
		case 10: //Enter press
		old_point = buffers[current_buffer] -> GetPoint(); //Get the old point location
		if(buffers[current_buffer] -> SearchF(search_pattern) == true)
		{
			new_point = buffers[current_buffer] -> GetPoint();
			strncpy((char*)search_pattern, "Pattern found", 13);
			MoveToSearch(buffers[current_buffer], old_point, new_point);
		}
		else strncpy((char*)search_pattern, "Pattern not found", 17);
		WriteSearch(search_pattern);
		refresh();
		ch = 0;
		while((ch = getch()) == 0); //spin the wheels until the user presses a key
		ClearBuff(); //clear the buffer
		break;
		case 18:
		mode = REPLACE;
		break;
		case 27:
		mode = VIEW;
		break;
		case ' ' ... '~': //regualr ascii character range
		InsertPtrn(_ch);
		break;
		case 263: //Backspace Press
		DeletePtrn();
		break;
		case 266: //F2 (Save)
		mode = SAVE;
		break;
		default:;
	}
}

void Controller::ParseReplace(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	uint8_t _ch = (uint8_t) ch;
	switch (ch)
	{
		case 6:
		mode = SEARCH;
		ClearBuff();
		break;
		case 9:
		mode = INSERT;
		break;
		case 27:
		mode = VIEW;
		break;
		case ' ' ... '~': //regualr ascii character range
		if(buffers[current_buffer] -> GetPoint() > 0 && buffers[current_buffer] -> GetPoint() <= buffers[current_buffer] -> GetTextLength()) //Inert into the current character
		{
			buffers[current_buffer] -> SetPointR(-1); //Go Back a character
			buffers[current_buffer] -> Delete(1); //Delete the "current character"
			buffers[current_buffer] -> SetPointR(1); //advance the cursor
			buffers[current_buffer] -> Insert(&_ch, 1); //insert the new character 
			//buffers[current_buffer] -> SetPointR(1); //advance the cursor

			AdvanceCursor(buffers[current_buffer], false);	
		}
		break;
		case 266: //F2 (Save)
		mode = SAVE;
		break;
		default:;
	}
}

void Controller::ParseInsert(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer)
{
	uint8_t _ch = (uint8_t) ch;
	int16_t offset = 0;
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
		buffers[current_buffer]->Insert(&_ch, 1);
		AdvanceCursor(buffers[current_buffer], false);	
		break;
		case 10: //Enter key Press
		buffers[current_buffer]->Insert(&_ch, 1);
		EndLine();
		break;
		case 263: //Backspace Press
                if(buffers[current_buffer]->GetPoint() > 0)
		{
			buffers[current_buffer] -> Delete(-1);
			RetractCursor(buffers[current_buffer], true);
		}
		break;
		case 258: //Down arrow press
		DeclinateCursor(buffers[current_buffer]);
		break;
		case 259: //Up arrow press
		InclinateCursor(buffers[current_buffer]);
		break;
		case 260: //Left arrow press 
		if(buffers[current_buffer] -> CheckLeft())
		{
			buffers[current_buffer] -> SetPointR(-1);
			RetractCursor(buffers[current_buffer], false);
		}
		break;
		case 261: //Right arrow press
		if(AdvanceCursor(buffers[current_buffer], true)) buffers[current_buffer]->SetPointR(1);
		break;
		case 266: //F2 (Save)
		mode = SAVE;
		break;
		case 330: //Delete key press
		if(buffers[current_buffer] -> GetPoint() <= buffers[current_buffer] -> GetTextLength()) buffers[current_buffer]->Delete(1); //if there is text to the right of the cursor then delete one line
		break;
		case 338: //Pg-Down //Go to end of current line
		offset = buffers[current_buffer] -> EndOfLine();
		buffers[current_buffer] -> SetPointR(offset);
		for(uint16_t i=0; i<offset; i++) AdvanceCursor(buffers[current_buffer], false); //move the cursor t othe end of the line
		break;
		case 339: //Pg-Up
		offset = buffers[current_buffer] -> BeginOfLine(); //Get the distance to the start of the line
		buffers[current_buffer] -> SetPointR(offset); //move the point there
		for(int16_t i=offset; i!=0; i++) RetractCursor(buffers[current_buffer], true); //move the cursor
		break;
		case 549: //Ctrl+Pg-Down
		offset = buffers[current_buffer] -> EndOfBuff(); //Get the distance to the end of the buffer
		for(uint16_t i=0; i<offset; i++) 
		{
			AdvanceCursor(buffers[current_buffer], false); //Order matters!
			buffers[current_buffer] -> SetPointR(1); //move the point there
		}
		break;
		case 554: //Ctrl+Pg-Up go to the begining of the file
		buffers[current_buffer] -> SetPointA(0);
		move(0, 0);
		break;
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
		case 258: //Down arrow press
		DeclinateCursor(buffers[current_buffer]);
		break;
		case 259: //Up arrow press
		InclinateCursor(buffers[current_buffer]);
		break;
		case 260: //Left arrow press 
		if(buffers[current_buffer] -> CheckLeft())
		{
			buffers[current_buffer] -> SetPointR(-1);
			RetractCursor(buffers[current_buffer], false);
		}
		break;
		case 261: //Right arrow press
		if(AdvanceCursor(buffers[current_buffer], true)) buffers[current_buffer]->SetPointR(1);
		break;
		case 266: //F2 (Save)
		mode = SAVE;
		break;
		default:;
	}
}

void Controller::Welcome(int32_t &ch)
{
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
 mode = INSERT; //Enter insert mode
}

void Controller::Save(uint8_t* action)
{
	*action = SAVE_ME;
	mode = VIEW; //switch to view mode when done
}

void Controller::SetRunning(bool* Running)
{
	running = Running;
}

void Controller::Control(vector<Buffer*> buffers, uint8_t current_buffer, uint8_t* action)
{
	if(ch == 268) *running = false; //if we get q then stop the program
	switch (mode) //check what mode we are in
	{
		case INSERT:
		curs_set(1); 
		display_status = true;
		ParseInsert(ch, buffers, current_buffer);
		break;
		
		case REPLACE:
		curs_set(1); 
		display_status = true;
		ParseReplace(ch, buffers, current_buffer);
		break;

		case SAVE:
		curs_set(0);
		display_status = false;
		Save(action);
		break;

		case SEARCH:
		curs_set(0); 
		display_status = false;
		ParseSearch(ch, buffers, current_buffer);
		break;

		case VIEW:
		curs_set(1); 
		display_status = true;
		ParseView(ch, buffers, current_buffer);
		break;

		case WELCOME:
		curs_set(0); 
		Welcome(ch);
		break;
		default:;
	}
	DrawScreen(buffers, current_buffer); //Draw the Screen
	if(display_status)
	{
		uint16_t y = 0;
		uint16_t x = 0;
		getyx(stdscr, y, x);
		WriteStatus(NULL, mode, ch, buffers[current_buffer]->GetLineNumber(), x+1);
	}
	else if(mode == SEARCH) WriteSearch(search_pattern);
        ch = getch(); //get the current character
}
