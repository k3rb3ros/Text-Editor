/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/includes.h"
#include "include/test.h"
#include "include/world.h"

int main(void)
{
	bool running = true;
	uint8_t make_it_work = 0;
	Test tests;
	tests.TestBuffer(); //test the basic buffer functions
	tests.TestDisplay(); //test the display (Visual Tests)
	World world;
	world.InitWindow();
	while(world.IsRunning())
	{
		world.control();
		world.DrawScreen(world.buffers, make_it_work);
	}
	world.FreeWindow();
	return 0;
}
