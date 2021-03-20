CPPFILES = ECEditorTest.cpp ECTextViewImp.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O4 -std=c++14 -Wall -I.

all:Editor

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Editor:$(OFILES)
	$(CC) -o Editor $(OFILES)

clean: 
	rm *.o
	rm Editor

