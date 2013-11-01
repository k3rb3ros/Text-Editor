#ifndef BUFFER_H
#define BUFFER_H

#include "includes.h"
#include "marker.h"

#define BUFFSIZE 10000

class Buffer
{
	private:
	bool modified;
	uint8_t buffer[BUFFSIZE];
	uint8_t* gap_end;
	uint8_t* gap_start;	
	uint8_t* point;
	uint16_t line_number;
	uint16_t text_length;

	public:
	Buffer(); //constructor
	bool GetModified();
	bool SearchF(uint8_t* txt);
	uint16_t GetGapE();
	uint16_t GetGapS();
	uint16_t GetLineNumber();
	uint16_t GetPoint();
	uint8_t GetCh(uint16_t index);
	void Delete(int32_t count);
	void Insert(uint8_t* txt, int32_t str_len);
	uint32_t GetTextLength();
	void SetLineNumber(int16_t line_num);
	void SetModified(bool status);
	void SetPointA(uint32_t location);
	void SetPointR(int32_t count);
	vector<Marker*> markers;
	~Buffer();
};

#endif
