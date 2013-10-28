#ifndef CONTROL_H
#define CONTROL_H

#include "buffer.h"
#include "includes.h"
#include "display.h"

class Controller : public Window 
{
	private:
	bool* running;
	//enum modes {SEARCH, REPLACE, INSERT, VIEW, WELCOME};
	int32_t ch;
	uint8_t mode;

	void ParseSearch(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void ParseReplace(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void ParseInsert(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void ParseView(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void Welcome(int32_t &ch);

	public:
	Controller();
	void SetRunning(bool* Running);
	void Control(vector<Buffer*> buffers, uint8_t current_buffer);
};

#endif 
