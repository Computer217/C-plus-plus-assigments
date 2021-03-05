CPPFILES = ECCommand.cpp ECTextDocument.cpp ECTextDocumentTest.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O4 -std=c++14 -Wall -I.

all: ModelViewController

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

ModelViewController:$(OFILES)
	$(CC) -o ModelViewController $(OFILES)

clean: 
	rm *.o
	rm ModelViewController

