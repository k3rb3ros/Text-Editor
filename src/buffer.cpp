#include "include/buffer.h"

Buffer::Buffer()
{
	modified = false; //set modified to false
	point = &buffer[0]; //set the point to point to the first index
	gap_end = &buffer[BUFFSIZE-1]; //set gap to point to the first index
	gap_start = &buffer[0]; //set gap start to the point
	for(uint32_t i=0; i<BUFFSIZE; i++) buffer[i] = 0; //zero fill the buffer
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
	return gap_end;
}

uint8_t* Buffer::GetPoint() //Returns the location of hte point
{
	return point;
}

uint8_t Buffer::GetCh(uint16_t index)
{
	if(index > text_length || index >= BUFFSIZE)
	{
		cerr << "Range not in buffer\n";
		return 0;
	}
	if(index >= (gap_end - gap_start)) return buffer[(gap_end - gap_start) + index];
	else return buffer[index];
}

void Buffer::Delete(int32_t count) //Deletes count uint8_t characters to the right of the point if count is positive; to the left of the point if count is negative
{
	if((point + count) < buffer || (point + count) > (buffer + BUFFSIZE)) cerr << "Invalid range to delete\n"; 
	else
	{
		if(count < 0)
		{
			count *= -1; //invert count
			for(int32_t i=0; i<count; i++) //delete characters to the left of point
			{
				*(point--) = 0; //delete the uint8_tacters left of the point and move the point to the left
				gap_start --; //update the start of the gap so that its at the new point
				text_length --;
			}
		}
		else if(count > 0)
		{
			for(int32_t i=0; i<count; i++) //delete characters to the right of point (after gap)
			{
				*(gap_end++) = 0; //delete the uint8_tacters right of the point
				text_length --;
			}
		}
	}	
}

void Buffer::Insert(uint8_t* txt, int32_t str_len) //insert a string at point, point ends up just after inserted text
{
	uint16_t offset = 0;
	if(str_len == 0)
	{
		cerr << "Text to insert is empty" << endl;
		return;
	}
	else if(text_length >= BUFFSIZE)
	{
		cerr << "Buffer is full unable to insert" << endl;
		return;
	}
	if(gap_start == point) //regular insert
	{
		for(uint16_t i=0; i<str_len; i++)
		{
			*(point++) = txt[i]; //insert the text at the point and advance it
			text_length ++; //keep track of how full the buffer is
			gap_start ++; //increment gap_start 
		}
	}
	else if(gap_start < point)//The cursor has been moved right so we should shift that many characters right of the gap left of it
	{
		offset = point - gap_start; //Get the offset
		memmove(gap_end, gap_start, offset); //move offset bits from right of the buffer to left of the buffer 
		gap_start = point; //update gap start to be at the same index as point
		gap_end +=offset; //expand the gap by the number of characters that we moved before it
		for(uint16_t i=0; i<str_len; i++) //insert the regular text
		{
			*(point++) = txt[i];
			text_length ++;
			gap_start ++; //increment gap_start 
		}
	}
	else //gap_start > point the cursor has been moved left so we should shift offset characters from left of the gap to right of the gap
	{
		offset = gap_start - point; 
		gap_start = point; //update gap start to be at the same index as point
		gap_end -= offset; //shrink the gap and expand the area of the text after it
		memmove(gap_start, gap_end, offset); //move the bits right of the gap
		for(uint16_t i=0; i<str_len; i++) //insert the regular text
		{
			*(point++) = txt[i];
			text_length ++;
			gap_start ++; //increment gap_start 
		}
	}
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
