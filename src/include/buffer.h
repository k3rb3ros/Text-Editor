#ifndef BUFFER_H
#define BUFFER_H

#include "includes.h"

#define BUFFSIZE 10000

class Buffer
{
	private:

	bool modified;
	uint8_t* gap;	
	uint8_t* point;
	uint8_t buffer[BUFFSIZE];
	uint32_t gap_length;
	uint32_t text_length;

	public:
	Buffer(); //constructor
	bool getModified();
	bool SearchF(uint8_t* txt);
	uint8_t* GetPoint();
	//void CreateBuffer(); //implicit in constructor
	void Delete(int32_t count);
	void Insert(uint8_t* txt);
	void SetModified();
	void SetPointA(uint32_t location);
	void SetPointR(uint32_t count);
	~Buffer();
};

#endif
