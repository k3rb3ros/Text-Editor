#ifndef DISPLAY_H
#define DISPLAY_H

#include "buffer.h"
#include "includes.h"

class Window
{
	private:
	uint16_t CursorPosLine(uint16_t line, map<uint16_t, Marker*> marks);
	void ClearLine(uint8_t* current_line, uint16_t len);
	void GetWindow(vector<Buffer*> &buffers, uint8_t &current_buffer, uint8_t* current_window, uint16_t &index, uint16_t &length_remaining);

	public:
	Window(); //default Constructor
	friend class World;
	bool AdvanceCursor(Buffer* buffer, bool check);
        void DeclinateCursor(Buffer* buffer);
	void DrawScreen(vector<Buffer*> &buffers, uint8_t &current_buffer);
	void EndLine(Buffer* buffer);
	void InclinateCursor(Buffer* buffer);
	void NcursesTest(); //Test ncurses
	void RetractCursor(Buffer* buffer, bool check);
	void WriteSearch(uint8_t* search);
	void WriteStatus(uint8_t* status, uint32_t mode, int32_t ch, uint32_t line_num, uint32_t column_num);
	~Window(); //Destructor
};

#endif
