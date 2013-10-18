#ifndef TEST_H
#define TEST_H

#include <assert.h>
#include "buffer.h"
#include "includes.h"
#include "world.h"

class Test
{
	Buffer test_buffer;
	World test_world;

	public:
	void TestBuffer();
	void TestCommandLoop(); //FIXME
	void TestDisplay(); //FIXME
	void TestWolrd(); //FIXME
	
};

#endif
