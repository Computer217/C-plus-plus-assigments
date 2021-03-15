CPPFILES = ECAbstractConvexPolygon.cpp ECCircle.cpp ECConvexPolygon.cpp ECLineSegment.cpp ECTriangle.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall -I.

all: Convex

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Convex:$(OFILES)
	$(CC) -o Convex $(OFILES)

clean: 
	rm *.o
	rm Convex

