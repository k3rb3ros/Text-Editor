#include "include/test.h"

void Test::TestBuffer()
{
	uint8_t text[] = "Hurpadurp\0";
	assert(test_buffer.GetModified() == false); //test modified is inited to false
	assert(test_buffer.GetGapLength() == 0); //test that gap length was inited to 0
	assert(test_buffer.GetTextLength() == 0); // and the text length was also inited to 0
	assert(test_buffer.GetGap() != NULL); //that GetGap is a valid pointer in to the buffer
	assert(test_buffer.GetPoint() != NULL); //as is GetPoint
	test_buffer.SetModified(true); //set modified to true
	assert(test_buffer.GetModified() == true); //test that modified was in fact set
	test_buffer.Insert(text);//put something in the buffer
	assert(test_buffer.GetTextLength() == 9); //test that the reported length is correct
	test_buffer.SetPointR(9); //move the point right 9 characters
	test_buffer.Delete(3);
	assert(test_buffer.GetTextLength() == 6);
	test_buffer.Delete(-3);
	assert(test_buffer.GetTextLength() == 3);
	cout << "Buffer Tests passed" << endl;
}
