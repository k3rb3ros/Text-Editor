#ifndef MARKER_H
#define MARKER_H

#include "includes.h"

class Marker
{
	protected:
	uint8_t type;
	uint8_t* begin;
	uint8_t* end;

	public:
        friend class Buffer;
        friend class Display;
	Marker(uint8_t Type); 
	uint8_t* GetBegin();
	uint8_t* GetEnd();
	void SetBegin(uint8_t* Begin);
	void SetEnd(uint8_t* End);
};

#endif
