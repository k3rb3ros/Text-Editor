#ifndef WORLD_H
#define WORLD_H

#include "buffer.h"
#include "control.h"
#include "display.h"
#include "includes.h"

class World : public Controller, public Window
{
        private:
	uint8_t current_buffer;
        uint8_t* file_name;

	protected:	
	bool running;
        
	public:
	friend class Controller;
	vector<Buffer*> buffers;
	
        World();
	World(uint8_t* FileName);
	bool IsRunning();
	uint8_t* GetFileName();
	uint8_t GetCurBuf();
	vector<Buffer*> GetBuffers();
	
	void AddBuffer();
	void DeleteBuffer(uint8_t buffer);
        void LoadWorld(uint8_t* FileName);
        void SaveWorld(uint8_t* FileName);
	//~World();
};
#endif
