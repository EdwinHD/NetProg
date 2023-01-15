.PHONY: all debug release clean

all: debug release

debug: TCP-dbg

TCP-dbg: main.cpp
	g++ -g -O0 main.cpp -o TCP-dbg -Wall

release: main

main: main.cpp
	g++ -O2 main.cpp -o main -DNDEBUG -Wall

clean:
	rm -f main TCP-dbg
