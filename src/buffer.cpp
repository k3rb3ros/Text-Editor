#include "include/buffer.h"

int16_t Buffer::SearchBuffer(uint8_t* pattern) //FIXME
{
	uint16_t i, j, M = strlen((char*)pattern);
	
	for(i=0, j=0; j<M&&i<text_length; i++, j++)
	{
		while(buffer[MapToGap(i)]!=pattern[j]) //if character in text does not match character in pattern then advance the pattern one character to the right in the test
		{
			if(pattern[j] == '?') break; //unless its a wildcard character
			i = i-j+1; 
			j=0;
		}
	}
	if(j==M) return i-M;
	else return -1;
}

Buffer::Buffer()
{
	modified = false; //set modified to false
	point = &buffer[0]; //set the point to point to the first index
	gap_end = &buffer[BUFFSIZE-1]; //set gap to point to the first index
	gap_start = &buffer[0]; //set gap start to the point
	for(uint32_t i=0; i<BUFFSIZE; i++) buffer[i] = 0; //zero fill the buffer
	text_length = 0;
}

bool Buffer::CheckLeft() //returns true if the character to the left of point is \n
{
	if((point-buffer) == 0 || *(point-1) == '\n') return false;
	return true;
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

bool Buffer::SearchF(uint8_t* ptrn)
{
	uint16_t len = strlen((char*) ptrn);
	int16_t search = SearchBuffer(ptrn);
	if(search >=0 && search < BUFFSIZE)
	{
		SetPointA(search);
		CreateMark(search, SEARCH_RESULT);
		SetMarkLen(search, len);	
		return true;
	}
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

uint16_t Buffer::GetCurrentLength()
{
	uint16_t length = 0;
	for(uint16_t i=0; i<(point-buffer); i++) if(buffer[MapToGap(i)]!='\n') length++;
	return length;
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
	uint16_t line_number = 1;
	for(uint16_t i = 0; i<=(point-buffer); i++)if(buffer[MapToGap(i)] == '\n') line_number++;
	return line_number;
}

uint16_t Buffer::GetNewX(uint16_t initial, uint16_t _new)
{
	uint16_t x = 0;
	uint16_t y = 0;
	
	getyx(stdscr, y, x); 
	if(initial < _new)
	{
		while(initial < _new)
		{
			if(buffer[MapToGap(initial++)] == '\n') x = 0;
			else x++;
		}
	}

	else if(initial > _new) //FIXME
	{
		while(initial > _new)
		{
			if(buffer[MapToGap(initial)] == '\n') x = 0; //if we encounter eol then the lines tarts over
			else if(x > 0) x--; //otherwise decriment x
			else if(x == 0) 
			{
				uint16_t count = initial;
				while(count != 0 && buffer[MapToGap(count--)] != '\n') // or set x to the length of the previous line
				{
					x++; 
				}
			}
			initial--;
		}
	}
	return x%CONSOLE_WIDTH;
}

uint16_t Buffer::GetNewY(uint16_t initial, uint16_t _new)
{
	int16_t x = 0;
	int16_t y = 0;

	getyx(stdscr, y, x);
	if(initial <= _new)
	{
		while(initial < _new)
		{
			if(buffer[MapToGap(initial++)] == '\n') 
			{
				x=0;
				y++;
			}
			else
			{
				x = (x + 1)%(CONSOLE_WIDTH+1); //increase X
				if(x == 0) y++; //if we reached the end of the line increment y
			}
		}		
	}
	
	else if(initial > _new) //FIXME
	{
		while(initial > _new)
		{
			if(buffer[MapToGap(initial)] == '\n') 
			{
				x=0;
				y--;
			}
			else if(x > 0) x--;
			else if(x == 0)
			{
				uint16_t count = initial;
				while(count != 0 && buffer[MapToGap(count--)] != '\n') // or set x to the length of the previous line
				{
					x++;
				}
				y--;
			}
			initial--;
		}
	}
	return y%(CONSOLE_HEIGHT-1);
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

uint16_t Buffer::LookLeft() //Get the x coordinate of the end of the previous line or the same one if it is longer then CONSOLE_WIDTH
{
	uint16_t count = 0; //used to count the length of line and mod it (in case its longer then CONSOLE_WIDTH
	uint16_t index = (point-buffer);
	uint16_t prev_line = index;
	if(buffer[MapToGap(prev_line-1)] == '\n') return 0; //case of \n\n x always = 0
	while(prev_line > 0 && buffer[MapToGap(prev_line-1)] != '\n') prev_line--; //Go to the begining of the previous line
	while(prev_line < index && buffer[MapToGap(++prev_line)] != '\n')//count the number of characters in that line and set that to x mod CONSOLE_WIDTH
	{	
		count++;
	}
	return count%CONSOLE_WIDTH; //return the x coordinate of that line
}

uint16_t Buffer::EndOfLine()//Get the number of characters after the point and before the next new line or end of text (whichever comes first)
{
	uint16_t index = (point - buffer);
	uint16_t length = 0;
	while(index < text_length && buffer[index++] != '\n') length++;
	return length;
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
		}
	}
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
