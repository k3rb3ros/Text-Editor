#ifndef WORLD_H
#define WORLD_H

#include "buffer.h"
#include "includes.h"

class World
{
        private:
        uint8_t* file_name;

	protected:
	uint8_t current_buffer;
	vector<Buffer> world;

        public:
        World();
	World(uint8_t* FileName);
	void AddBuffer();
	void DeleteBuffer(uint8_t buffer);
        void LoadWorld(uint8_t* FileName);
        void SaveWorld(uint8_t* FileName);
};
#endif
