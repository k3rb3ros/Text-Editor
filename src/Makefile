####################################################
# Makefile for text editor written for CSCI480@CMU #
####################################################
CC=g++
DEPS=include/*.h
CFLAGS=-std=c++11 -O0 -g -Wall -Wextra
IFLAGS=-I /usr/include/ncursesw
LPATHS=-L/usr/lib/x86_64-linux-gnu
LFLAGS=-lncursesw
SRCES=$(wildcard *.cpp)
OBJDIR=objects
OBJS=$(SRCES:.cpp=.o)
BINARY=kedit

all: $(BINARY) $(OBJS)
.cpp.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $(OBJDIR)/$@
	
$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LPATHS) $(addprefix $(OBJDIR)/,$(OBJS)) -o $@ $(LFLAGS)

.PHONY: clean

clean: 
	rm -fv $(BINARY) objects/*.o
