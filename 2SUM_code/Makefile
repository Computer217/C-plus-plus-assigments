CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall

all: 2SUM


ECBinSearch.o : ECBinSearch.cpp  ECBinSearch.h
	$(CC)  $(CFLAGS) -c ECBinSearch.cpp

ECSort.o : ECSort.cpp  ECSort.h
	$(CC)  $(CFLAGS) -c ECSort.cpp

EC2SUM.o : EC2SUM.cpp  EC2SUM.h
	$(CC)  $(CFLAGS) -c EC2SUM.cpp

EC2SUMmain.o : EC2SUMmain.cpp 
	$(CC)  $(CFLAGS) -c EC2SUMmain.cpp

2SUM: ECBinSearch.o ECSort.o EC2SUM.o EC2SUMmain.o 
	$(CC) -o 2SUM ECBinSearch.o ECSort.o EC2SUM.o EC2SUMmain.o
