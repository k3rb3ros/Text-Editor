#ifndef CONTROL_H
#define CONTROL_H

#include "buffer.h"
#include "includes.h"
#include "display.h"

class Controller : public Window 
{
	private:
	bool display_status;
	bool* running;
	int32_t ch;
	uint8_t mode;
	
	void DeletePtrn();
	void InsertPtrn(uint8_t ch);	
	void ClearBuff();
	void ParseSearch(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void ParseReplace(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void ParseInsert(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void ParseView(int32_t ch, vector<Buffer*> buffers, uint8_t current_buffer);
	void Save(uint8_t* action);
	void Welcome(int32_t &ch);
	
	protected:
	uint8_t search_pattern[CONSOLE_WIDTH+1];

	public:
	friend class Window;

	Controller();
	void SetRunning(bool* Running);
	void Control(vector<Buffer*> buffers, uint8_t current_buffer, uint8_t* action);
};

#endif 
