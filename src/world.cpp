/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/world.h"

World::World()
{
	world = new Buffer; 
	file_name = NULL;
}

World::World(uint8_t* FileName)
{
	world = new Buffer;
	file_name = FileName; 
}

void World::LoadWorld(uint8_t* FileName)
{
	//FIXME
	//Load the world from the file given
}

void World::SaveWorld(uint8_t* FileName)
{
	//FIXME
	//Save the world to the file given
}
