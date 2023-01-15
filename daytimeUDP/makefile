.PHONY: all debug release clean

all: debug release

debug: UDP-dbg

UDP-dbg: main.cpp
	g++ -g -O0 main.cpp -o UDP-dbg -Wall

release: main

main: main.cpp
	g++ -O2 main.cpp -o main -DNDEBUG -Wall

clean:
	rm -f main UDP-dbg
