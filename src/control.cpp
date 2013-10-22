/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/
#include "include/control.h"

void Controller::ParseSearch(int32_t ch)
{
	switch (ch)
	{
		case 0:
		break;
		default:;
	}
}

void Controller::ParseReplace(int32_t ch)
{
	switch (ch)
	{
		case 0:
		break;
		default:;
	}
}

void Controller::ParseInsert(int32_t ch)
{
	switch (ch)
	{
		case 0:
		break;
		default:;
	}
}

void Controller::ParseView(int32_t ch)
{
	switch (ch)
	{
		case 0:
		break;
		default:;
	}
}

void Controller::control()
{
	int32_t ch = getch(); //get the current character
	if(ch == 'q') printw("stop this shit!\n");; //if we get q then stop the program
	switch (mode)
	{
		case SEARCH: ParseSearch(ch);
		break;

		case REPLACE: ParseReplace(ch);
		break;

		case INSERT: ParseInsert(ch);
		break;

		case VIEW: ParseView(ch);
		break;
		default:;
	}
}
