CPPFILES = ECLineSegment.cpp ECTriangle.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall -I.

all: Geometry

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Geometry:$(OFILES)
	$(CC) -o Geometry $(OFILES)

clean: 
	rm *.o
	rm Geometry

