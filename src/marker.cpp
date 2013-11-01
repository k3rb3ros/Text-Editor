#include "include/marker.h"

Marker::Marker(uint8_t Type)
{
    type = Type;
    begin = NULL;
    end = NULL;
}

uint8_t* Marker::GetBegin()
{
    return begin;
}

uint8_t* Marker::GetEnd()
{
    return end;
}

void Marker::SetBegin(uint8_t* Begin)
{
    begin = Begin;
}

void Marker::SetEnd(uint8_t* End)
{
    end = End;
}
