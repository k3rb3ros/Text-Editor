#include "includes/memory_management.h"

Buffer::Buffer()
{
	for(uint32_t i=0; i<BUFFSIZE; i++) buffer[i] 0; //zero fill the buffer
	point = &buffer[0];
}

bool SearchF(char* txt)
{
	return false;
}

char* Buffer::GetPoint() //Returns the location of hte point
{
	return point;
}

void Buffer::Delete(uint32_t count) //Deletes count characters to the right of the point if count is positive; to the left of the point if count is negative
{
	if(*(point+count) < *buffer || *(point+count) > *(buffer + BUFFSIZE)) cerror << "Invalid range to delete\n"; 
	else
	{
		if(count < 0)
		{
			count *= -1; //invert count
			for(uint32_t i=0; i<count; i++) buffer[point--] = 0; //delete the characters left of the point and move the point to the left
		}
		else if(count > 0)
		{
			for(uint32_t i=0; i<count; i++) buffer[point++] = 0; //delete the characters right of the point
		}
	}	
}

void Buffer::Insert(char* txt) //insert a string at point, point ends up just after inserted text
{
	uint32_t len = strlen(txt); //get the length of the string
	for(uint32_t i; i<len; i++) buffer[point++] = txt[i]; //insert the text at the point and advance it
}

void Buffer::SetPointA(uint32_t location); //set the point to location
{
	if(location >= 0 && location < BUFFSIZE)
	{
		point = *(buffer + location); //set the piont to the absolute location
	}
	else cerr << "Unable to set point; Location is outside of buffer range \n";
}

void Buffer::SetPointR(uint32_t count) //Moves the point count characters relative to the current location
{
	if((point + count) > buffer && (point + count) >= (buffer + BUFFSIZE))
	{
		point = *(point+count); //set the point
	}
	else cerr << "Unable to set point; Location is outside of buffer range \n";
}

Buffer::~Buffer()
{
}
