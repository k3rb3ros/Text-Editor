/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/includes.h"
#include "include/display.h"
#include "include/test.h"
#include "include/world.h"

int main(void)
{
	Test tests;
	tests.TestBuffer();
	World TheWorld;
	Window main;
	main.NcursesTest();
	return 0;
}
