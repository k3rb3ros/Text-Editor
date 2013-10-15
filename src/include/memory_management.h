#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include "includes.h"

#define BUFFSIZE 100000

class Buffer
{
	private:
	
	char* point;
	char buffer[BUFFSIZE];

	public:
	Buffer(); //constructor
	bool SearchF(char* txt);
	char* GetPoint();
	//void CreateBuffer(); //implicit in constructor
	void Delete(int32_t count);
	void Insert(char* txt);
	void SetPointA(uint32_t location);
	void SetPointR(uint32_t count);
	~Buffer();
};

#endif
