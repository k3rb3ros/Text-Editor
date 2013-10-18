/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/world.h"

World::World()
{
	Buffer temp;
	world.push_back(temp); 
	current_buffer = 1;
	file_name = NULL;
}

World::World(uint8_t* FileName)
{
	Buffer temp;
	world.push_back(temp);
	current_buffer = 1; 
	file_name = FileName; 
}

void World::AddBuffer()
{
	Buffer temp;
	world.push_back(temp);
}

void World::DeleteBuffer(uint8_t buffer)
{
	if(world.size() > 1)
	{
		world.erase(world.begin()+buffer);
	}
	else cerr << "Can't delete default buffer" << endl;
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
