#ifndef BUFFER_H
#define BUFFER_H

#include "includes.h"

#define BUFFSIZE 10000

class Buffer
{
	private:
	bool modified;
	uint8_t buffer[BUFFSIZE];
	uint8_t* gap_end;
	uint8_t* gap_start;	
	uint8_t* point;
	uint16_t text_length;

	public:
	Buffer(); //constructor
	bool GetModified();
	bool SearchF(uint8_t* txt);
	uint8_t* GetGap();
	uint8_t* GetPoint();
	uint8_t GetCh(uint16_t index);
	//void CreateBuffer(); //implicit in constructor
	void Delete(int32_t count);
	void Insert(uint8_t* txt);
	uint32_t GetTextLength();
	void SetModified(bool status);
	void SetPointA(uint32_t location);
	void SetPointR(uint32_t count);
	~Buffer();
};

#endif
