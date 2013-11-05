#include "include/buffer.h"

Buffer::Buffer()
{
	modified = false; //set modified to false
	point = &buffer[0]; //set the point to point to the first index
	gap_end = &buffer[BUFFSIZE-1]; //set gap to point to the first index
	gap_start = &buffer[0]; //set gap start to the point
	for(uint32_t i=0; i<BUFFSIZE; i++) buffer[i] = 0; //zero fill the buffer
	line_number = 1;
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

bool Buffer::SetMarkLen(uint16_t index, uint16_t len)
{
        Marker* mark = NULL;
        uint16_t gap_index = MapToGap(index);
	if(markers.find(gap_index) == markers.end()) return false; //if a mark doesn't exist at this index then return false
         mark = markers[gap_index];
	 mark -> end = (mark -> begin + len); //otherwise set its length
	return true;
}

uint32_t Buffer::GetTextLength()
{
	return text_length;
}

uint16_t Buffer::GetGapE()
{
	return (gap_end - buffer);
}

uint16_t Buffer::GetGapS()
{
	return (gap_start - buffer);
}

uint16_t Buffer::GetLineNumber()
{
	return line_number;
}

uint16_t Buffer::GetPoint() //Returns the location of the point
{
	return (point - buffer);
}

uint16_t Buffer::MapToGap(uint16_t index) //Map a character index in the array to its actual position
{
	if(index >= BUFFSIZE) return 0;
	
  	if(index < GetGapS()) return index;
  	else return(index-GetGapS()+GetGapE());
}

uint8_t Buffer::GetCh(uint16_t index)
{
	if(index > text_length || index >= BUFFSIZE)
	{
		return 0;
	}
	return buffer[MapToGap(index)]; 
}

void Buffer::CreateMark(uint16_t index, uint8_t type)
{
        uint16_t gap_index = MapToGap(index);
	Marker* mark = new Marker(type);
        
	mark -> begin = &buffer[gap_index];
	mark -> end = mark -> begin+1; //Set the end
	
        markers.insert(pair<uint16_t, Marker*>(gap_index, mark)); //map our mark to the buffer
}

void Buffer::DeleteMark(uint16_t index)
{
        markers.erase(MapToGap(index));
}

void Buffer::Delete(int32_t count) //Deletes count uint8_t characters to the right of the point if count is positive; to the left of the point if count is negative
{
	if((point + count) < buffer || (point + count) > (buffer + BUFFSIZE)) cerr << "Invalid range to delete\n"; 
	else
	{
	    if(text_length > 0)
            {
		if(count < 0)
		{
			count *= -1; //invert count
			for(int32_t i=0; i<count; i++) //delete characters to the left of point
			{
				if(*point == '\n') line_number--;
				*(point--) = 0; //delete the uint8_tacters left of the point and move the point to the left
				gap_start --; //update the start of the gap so that its at the new point
				text_length --;
			}
		}
		else if(count > 0)
		{
			for(int32_t i=0; i<count; i++) //delete characters to the right of point (after gap)
			{
				if(*gap_end == '\n') line_number--;
				*(gap_end++) = 0; //delete the uint8_tacters right of the point
				text_length --;
			}
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
	else if(gap_end == gap_start)
	{
		cerr << "Buffer is full unable to insert" << endl;
		return;
	}
	/*else if(text_length >= BUFFSIZE)
	{
		cerr << "Buffer is full unable to insert" << endl;
		return;
	}*/
	if(gap_start == point) //regular insert
	{
		for(uint16_t i=0; i<str_len; i++)
		{
			*(point++) = txt[i]; //insert the text at the point and advance it
			if(txt[i] == '\n') line_number++;
			text_length += str_len; //keep track of how full the buffer is
			gap_start ++; //increment gap_start 
		}
	}
	else if(gap_start < point)//The cursor has been moved right so we should shift that many characters right of the gap left of it
	{
		offset = point - gap_start; //Get the offset
		memmove(gap_start, gap_end, offset); //move the bits right of the gap
		gap_start = point; //update gap start to be at the same index as point
		gap_end +=offset; //expand the gap by the number of characters that we moved before it
		for(uint16_t i=0; i<str_len; i++) //insert the regular text
		{
			*(point++) = txt[i];
			if(txt[i] == '\n') line_number++;
			text_length += str_len;
			gap_start ++; //increment gap_start 
		}
	}
	else //gap_start > point the cursor has been moved left so we should shift offset characters from left of the gap to right of the gap
	{
		offset = gap_start - point; 
		
		gap_end -= offset; //shrink the gap and expand the area of the text after it
		memmove(gap_end, point, offset); //move offset bits from right of the buffer to left of the buffer 
		gap_start = point; //update gap start to be at the same index as point
		for(uint16_t i=0; i<str_len; i++) //insert the regular text
		{
			*(point++) = txt[i];
			if(txt[i] == '\n') line_number++;
			text_length += str_len;
			gap_start ++; //increment gap_start 
		}
	}
}

void Buffer::SetLineNumber(int16_t line_num)
{
	line_number += line_num;
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

void Buffer::SetPointR(int32_t count) //Moves the point count characters relative to the current location
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
