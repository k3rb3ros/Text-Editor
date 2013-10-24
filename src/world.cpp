/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/world.h"

World::World()
{
	Buffer* temp = new Buffer;
	buffers.push_back(temp); 
	current_buffer = 0;
	file_name = NULL;
	running = true;
	control.SetRunning(&running);
}

World::World(uint8_t* FileName)
{
	Buffer* temp = new Buffer;
	buffers.push_back(temp);
	current_buffer = 1; 
	file_name = FileName; 
	running = true;
	control.SetRunning(&running);
}

bool World::IsRunning()
{
	return running;
}

uint8_t* World::GetFileName()
{
	return file_name;
}

uint8_t World::GetCurBuf()
{
	return current_buffer;
}

vector<Buffer*> World::GetBuffers()
{
	return buffers;
}

void World::AddBuffer()
{
	Buffer* temp = new Buffer;
	buffers.push_back(temp);
}

void World::Control()
{
	control.Control(buffers, current_buffer);
}

void World::DeleteBuffer(uint8_t buffer)
{
	if(buffers.size() > 1)
	{
		buffers.erase(buffers.begin()+buffer);
	}
	else cerr << "Can't delete default buffer" << endl;
}

void World::LoadWorld(uint8_t* FileName)
{
	//FIXME
	//Load the world from the file given
}

void World::ReDisplay()
{
	display.DrawScreen(buffers, current_buffer);		
}

void World::SaveWorld(uint8_t* FileName)
{
	//FIXME
	//Save the world to the file given
}
