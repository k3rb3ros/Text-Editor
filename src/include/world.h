#ifndef WORLD_H
#define WORLD_H

#include "buffer.h"
#include "display.h"
#include "includes.h"

class World : public Window
{
        private:
	bool running;
	uint8_t current_buffer;
        uint8_t* file_name;

	protected:
	//bool running;
	//uint8_t current_buffer;
        //uint8_t* file_name;

        public:
        World();
	World(uint8_t* FileName);
	uint8_t GetCurBuf();
	void AddBuffer();
	void DeleteBuffer(uint8_t buffer);
        void LoadWorld(uint8_t* FileName);
        void SaveWorld(uint8_t* FileName);
	vector<Buffer*> buffers;
};
#endif
