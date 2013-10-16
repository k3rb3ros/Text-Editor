#ifndef WORLD_H
#define WORLD_H

#include "buffer.h"
#include "includes.h"

class World
{
        private:

        Buffer* world;
        uint8_t* file_name;

        public:
        World();
	World(uint8_t* FileName);
        void LoadWorld(uint8_t* FileName);
        void SaveWorld(uint8_t* FileName);
};
#endif
