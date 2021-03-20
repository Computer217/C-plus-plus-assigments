CPPFILES = ECTriangle.cpp ECLineSegment.cpp ECConvexPolygon.cpp ECCompositeShapes.cpp ECCircle.cpp ECAbstractConvexPolygon.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O4 -std=c++11 -Wall -I.

all: Convex

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Convex:$(OFILES)
	$(CC) -o Convex $(OFILES)

clean: 
	rm *.o
	rm Convex

