#ifndef CONTROL_H
#define CONTROL_H

#include "buffer.h"
#include "includes.h"
#include "display.h"

class Controller 
{
	private:
	enum modes {SEARCH, REPLACE, INSERT, VIEW};
	uint8_t mode;

	void ParseSearch(int32_t ch);
	void ParseReplace(int32_t ch);
	void ParseInsert(int32_t ch);
	void ParseView(int32_t ch);

	public:
	void control();
};

#endif 
