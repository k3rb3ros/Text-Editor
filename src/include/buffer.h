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

	uint16_t SearchBuffer(uint8_t* pattern);
        
        protected:
	map<uint16_t, Marker*> markers;

	public:
	Buffer();
	bool CheckLeft();
	bool GetModified();
	bool LookRight();
	bool SearchF(uint8_t* ptrn);
        bool SetMarkLen(uint16_t index, uint16_t len);
	int32_t LookBackward(int32_t x);
        int32_t LookForward(int32_t x);
	uint32_t GetTextLength();
	uint16_t GetGapE();
	uint16_t GetGapS();
	uint16_t GetLineNumber();
	uint16_t GetMark(uint16_t index);
	uint16_t GetPoint();
	uint16_t GoBackALine(uint16_t x);
	uint16_t LookLeft();
        uint16_t MapToGap(uint16_t index);
	uint8_t GetCh(uint16_t index);
	void CreateMark(uint16_t index, uint8_t type);
	void DeleteMark(uint16_t index);
	void Delete(int32_t count);
	void Insert(uint8_t* txt, int32_t str_len);
	void SetLineNumber(int16_t line_num);
	void SetModified(bool status);
	void SetPointA(uint32_t location);
	void SetPointR(int32_t count);
	~Buffer();
};

#endif
