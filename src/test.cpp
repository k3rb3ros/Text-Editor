#include "include/test.h"

void Test::TestBuffer()
{
	uint8_t text[] = "Hurpadurp\0";
	assert(test_buffer.GetModified() == false); //test modified is inited to false
	assert(test_buffer.GetTextLength() == 0); // and the text length was also inited to 0
	assert(test_buffer.GetGapS() == test_buffer.GetPoint()); //that GetGap is a valid pointer in to the buffer
	assert(test_buffer.GetGapE() == BUFFSIZE-1);
	assert(test_buffer.GetPoint() == 0); //as is GetPoint
	test_buffer.SetModified(true); //set modified to true
	assert(test_buffer.GetModified() == true); //test that modified was in fact set
	test_buffer.Insert(text, 9);//put something in the buffer
	assert(test_buffer.GetTextLength() == 9); //test that the reported length is correct
	test_buffer.SetPointR(9); //move the point right 9 characters
	test_buffer.Delete(3);
	assert(test_buffer.GetTextLength() == 6);
	test_buffer.Delete(-3);
	assert(test_buffer.GetTextLength() == 3);
	cout << "Buffer Tests passed" << endl;
}

void Test::TestDisplay()
{
/*
	World display_test;
	uint8_t test = 0;
	uint8_t text[] = "Hurpadurp\nHere is some sample text that I want to type\nTo test weather or not I can display correctly\n\0";
	display_test.GetBuffers()[display_test.GetCurBuf()]->Insert(text);
	assert(display_test.buffers[display_test.GetCurBuf()]->GetTextLength() > 0);
	display_test.DrawScreen(display_test.buffers, test);
	cout << "Display Tests passed" << endl;
*/
}
