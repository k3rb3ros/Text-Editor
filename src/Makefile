####################################################
# Makefile for text editor written for CSCI480@CMU #
####################################################
CC=g++
CFLAGS=-std=c++11 -O0 -g -Wall -Wextra
LDFLAGS=
SOURCES=main.cpp
OBJECTS_DIR=objects/
OBJECTS=$(SOURCES:.cpp=.o)
BINARY=kedit

all: $(BINARY) $(OJECTS_DIR)$(OBJECTS)
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $(OBJECTS_DIR)$@

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS_DIR)$(OBJECTS) -o $@

clean: 
	rm -fv $(BINARY) $(OBJECTS_DIR)$(OBJECTS)
