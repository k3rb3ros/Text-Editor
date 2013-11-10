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

bool Buffer::LookRight()
{
	uint32_t index = (point - buffer);
	if(index < text_length && buffer[MapToGap(index+1)] != '\n') return true; //if we are still in the text and the character to the right isn't the start of a new line continue with the operation
	return false;
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

int32_t Buffer::LookBackward(int32_t x)//Return the x coordinate of the previous line if it exists otherwise the x coordinate of the end of the previous line or -1 if there is no previous line
{
	uint32_t i = (point - buffer);
	while(i >= 0)
	{
		if(buffer[MapToGap(i--)] == '\n')//check for previous lines
		{
			uint32_t j = 0;
			while(i>0 && buffer[MapToGap(i--)] != '\n'); //go to the begining of the previous line
			while(j < x) if(buffer[MapToGap(i+j)] != '\n') j++;
			else break; //advance j until the line ends or we reach x
			SetPointA(i+j); //Set the point there
			return j; //return the x offset to that point
		}
	}
	return -1; //There are no previous lines 
}

int32_t Buffer::LookForward(int32_t x) //Search forward if there is another line continue until you get to the current x value of the cursor or we reach the end of the text
{
        uint32_t i = (point - buffer); //get the count for length calculations 

        while(i <= text_length)
        {
                if(buffer[MapToGap(i++)]=='\n') //find the start of the next line //afterwards increment the index
                {
                        int32_t j = 0;
                        for(j=0; j<x; ++j) if(i+j == text_length) break; //advance j to x or the end of the line whichever comes first
                        SetPointA(i+j); //Set the point to the new cursor position                
                        return j%CONSOLE_WIDTH; //return the horizontal the new horizontal position of the cursor
                }
        }
        return -1;
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

uint16_t Buffer::GoBackALine(uint16_t x)
{
        uint16_t point = GetPoint();
	
	return 0;
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
	map<uint16_t, Marker*>::iterator it; //declare a map iterator (for find)
	it = markers.find(gap_index);

	if(it != markers.end())
	{
		Marker* mark = new Marker(type);
        
		mark -> begin = &buffer[gap_index];
		mark -> end = mark -> begin+1; //Set the end	
        	markers[gap_index] = mark; //map our mark to the buffer
	}
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
			gap_start ++; //increment gap_start 
			text_length += str_len; //keep track of how full the buffer is
			if(txt[i] == '\n') line_number++;
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
			gap_start ++; //increment gap_start 
			text_length += str_len;
			if(txt[i] == '\n') line_number++;
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
			gap_start ++; //increment gap_start 
			text_length += str_len;
			if(txt[i] == '\n') line_number++;
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
   map<uint16_t, Marker*>::iterator it;
   for(it=markers.begin(); it!=markers.end(); ++it)
   {
     delete it->second;
   }
}
