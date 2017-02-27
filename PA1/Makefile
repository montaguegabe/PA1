CPPFLAGS=-g -std=c++0x
LDFLAGS=-g

randmst: main.o main.cpp MST.h Random.h Types.h Util.h
	g++ $(LDFLAGS) -o randmst main.o

randmst.o: main.cpp MST.h Random.h Types.h Util.h
	g++ $(CPPFLAGS) -c main.cpp

clean:
	rm ./randmst
	rm main.o
