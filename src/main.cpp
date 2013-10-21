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
	tests.TestBuffer(); //test the basic buffer functions
	tests.TestDisplay(); //test the display (Visual Tests)
	World TheWorld;
	//TheWorld.InitWindow();
	//TheWorld.DrawScreen(TheWorld.world, 1);
	//TheWorld.FreeWindow();
	return 0;
}
