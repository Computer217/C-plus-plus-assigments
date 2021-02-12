CPPFILES = ECArrayofStrings.cpp ECArrayofStringsMain.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall -I.

all: ArrayofStrings

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

ArrayofStrings:$(OFILES)
	$(CC) -o ArrayofStrings $(OFILES)

clean: 
	rm *.o
	rm ArrayofStrings

