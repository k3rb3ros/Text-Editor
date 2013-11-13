#ifndef WORLD_H
#define WORLD_H

#include "buffer.h"
#include "control.h"
#include "display.h"
#include "includes.h"

class World 
{
        private:
	bool running;
	Controller control;
	uint8_t current_buffer;
        uint8_t* file_name;
	vector<Buffer*> buffers;

	protected:
	uint8_t action;	
        
	public:
	friend class Controller;
        World();
	World(uint8_t* FileName);
	bool IsRunning();
	uint8_t* GetFileName();
	uint8_t GetCurBuf();
	vector<Buffer*> GetBuffers();
	
	void AddBuffer();
	void Control();
	void DeleteBuffer(uint8_t buffer); //FIXME
        void LoadWorld(uint8_t* FileName);
        void SaveWorld(uint8_t* FileName);
	~World();
};
#endif

