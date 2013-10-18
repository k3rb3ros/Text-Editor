#include "include/buffer.h"

Buffer::Buffer()
{
	modified = false; //set modified to false
	gap = &buffer[0]; //set gap to point to the first index
	point = &buffer[0]; //set the point to point to the first index
	for(uint32_t i=0; i<BUFFSIZE; i++) buffer[i] = 0; //zero fill the buffer
	gap_length = 0;
	text_length = 0;
}

bool Buffer::GetModified()
{
	return modified;
}

bool Buffer::SearchF(uint8_t* txt)
{
	return false;
}

uint8_t* Buffer::GetGap()
{
	return gap;
}

uint8_t* Buffer::GetPoint() //Returns the location of hte point
{
	return point;
}

void Buffer::Delete(int32_t count) //Deletes count uint8_t characters to the right of the point if count is positive; to the left of the point if count is negative
{
	if((point + count) < buffer || (point + count) > (buffer + BUFFSIZE)) cerr << "Invalid range to delete\n"; 
	else
	{
		if(count < 0)
		{
			count *= -1; //invert count
			for(int32_t i=0; i<count; i++) 
			{
				*(point--) = 0; //delete the uint8_tacters left of the point and move the point to the left
				text_length --;
			}
		}
		else if(count > 0)
		{
			for(int32_t i=0; i<count; i++)
			{
				*(point++) = 0; //delete the uint8_tacters right of the point
				text_length --;
			}
		}
	}	
}

void Buffer::Insert(uint8_t* txt) //insert a string at point, point ends up just after inserted text
{
	uint32_t len = strlen((const char*)txt); //get the length of the string
	if(len == 0) cerr << "Text to insert is empty" << endl;
	for(uint32_t i=0; i<len; i++)
	{
		*(point++) = txt[i]; //insert the text at the point and advance it
		text_length ++;
	}
}

uint32_t Buffer::GetGapLength()
{
	return gap_length;
}

uint32_t Buffer::GetTextLength()
{
	return text_length;
}

void Buffer::SetModified(bool status)
{
 	modified = status;
}

void Buffer::SetPointA(uint32_t location) //set the point to location
{
	if(location < BUFFSIZE)
	{
		point = (buffer + location); //set the piont to the absolute location
	}
	else cerr << "Unable to set point; Location is outside of buffer range \n";
}

void Buffer::SetPointR(uint32_t count) //Moves the point count uint8_tacters relative to the current location
{
	if((point + count) > buffer && (point + count) < (buffer + BUFFSIZE))
	{
		point = (point+count); //set the point
	}
	else cerr << "Unable to set point; Location is outside of buffer range \n";
}

Buffer::~Buffer()
{
}
