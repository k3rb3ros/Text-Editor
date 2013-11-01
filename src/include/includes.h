#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define LINE 0x1
#define SELECTION 0x2
#define SEARCH_RESULT 0x4

enum modes {SEARCH, REPLACE, INSERT, VIEW, WELCOME};

#endif
