# Makefile

OPTIONS = -g -o2 -Wall -std=c++11

all: shell

shell: main.cpp inode.o bloc.o element.o parser.o
	g++ $(OPTIONS) -o shell main.cpp inode.o bloc.o element.o parser.o
	
inode.o: inode.cpp inode.h
	g++ $(OPTIONS) -c -o inode.o inode.cpp
	
bloc.o: bloc.cpp bloc.h
	g++ $(OPTIONS) -c -o bloc.o bloc.cpp
	
element.o: element.cpp element.h
	g++ $(OPTIONS) -c -o element.o element.cpp

parser.o: CMD/parser.cpp CMD/parser.h
	g++ $(OPTIONS) -c -o parser.o CMD/parser.cpp

clean:
	rm -f shell
	rm -rf shell.*
	rm -f *.o

y1: clean all
	./shell
