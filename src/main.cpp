/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/includes.h"
#include "include/test.h"
#include "include/world.h"

int main(void)
{
	uint8_t make_it_work = 0;
	World world;
	while(world.IsRunning())
	{
		world.Control();
		world.ReDisplay();
	}
	return 0;
}
