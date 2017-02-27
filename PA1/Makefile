CPPFLAGS=-g -std=c++11
LDFLAGS=-g

randmst: main.o
	g++ $(LDFLAGS) -o randmst main.o

randmst.o: main.cpp MST.h Random.h Types.h Util.h
	g++ $(CPPFLAGS) -c main.cpp
