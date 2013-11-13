/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/includes.h"
#include "include/test.h"
#include "include/world.h"

int main(int argc, char** argv)
{
	World* world;
	if(argc == 1) world = new World; //Default ctor
	else if(argc == 2) world = new World((uint8_t*)argv[1]); //create world with file name
	while(world -> IsRunning())
	{
		world -> Control();
	}
	delete world;
	return 0;
}
