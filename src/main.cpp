/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/includes.h"
#include "include/test.h"
#include "include/world.h"

int main(void)
{
	World world;
	while(world.IsRunning())
	{
		world.Control();
	}
	return 0;
}
