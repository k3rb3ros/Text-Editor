/*
* Simple text editor 
* written by Ryan Morris for CSCI480
*/

#include "include/world.h"

World::World()
{
	action = NONE;
	Buffer* temp = new Buffer;
	buffers.push_back(temp); 
	current_buffer = 0;
	file_name = NULL;
	running = true;
	control.SetRunning(&running);
}

World::World(uint8_t* FileName)
{
	action = NONE;
	Buffer* temp = new Buffer;
	buffers.push_back(temp);
	current_buffer = 0; 
	file_name = FileName;
	running = true;
	control.SetRunning(&running);
	LoadWorld(FileName);
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
	if(action == SAVE_ME);// DO SAVE
	control.Control(buffers, current_buffer, &action);
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
	ifstream inf((char*)FileName);
	if(inf)
	{
		uint8_t ch = 0;
		uint16_t file_length = 0;
		inf.seekg(0, inf.end);
		file_length = inf.tellg(); //get the length of the file
		inf.seekg(0, inf.beg);
		while(inf >> ch)
		{
			buffers[current_buffer] -> Insert(&ch, 1); //not efficient but it works
		}	
		inf.close();
		buffers[current_buffer]->SetPointA(0); //Set Point to the begining of the file
	}
	//Load the world from the file given
}

void World::SaveWorld(uint8_t* FileName)
{
	ofstream outf((char*)FileName);
	if(outf)
	{
		outf.close();
	}
	//Save the world to the file given
}

World::~World()
{
	delete buffers[0]; //free the default buffer
	buffers.erase(buffers.begin());
}
