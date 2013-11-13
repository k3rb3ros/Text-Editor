#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <fstream>
#include <map>
#include <ncurses.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define CONSOLE_HEIGHT 23
#define CONSOLE_WIDTH 80

//Mark types and actions
#define NONE 0x0
#define EOL 0x1
#define SELECTION 0x2
#define SEARCH_RESULT 0x4
#define SAVE_ME 0x8

//modes of controller operation
enum modes {INSERT, REPLACE, SAVE, SEARCH, VIEW, WELCOME};

#endif
