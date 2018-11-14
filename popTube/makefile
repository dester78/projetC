#CC current variable for compiler in C 
CC=gcc

S_DIR=D:\projetC\popTube\src

CPPFLAGS = -I D:\projetC\popTube\include -I 'C:\Program Files (x86)\MySQL\MySQL Connector C 6.1\include'


#CFLAGS current variable for compilation options   
#-W et -Wall display front end compiler warnings 
#-ansi request ansi compilation 
#-pedantic display compiler warnings 
CFLAGS=-W -Wall -ansi -pedantic -std=c99 

#LDFLAGS current variable for link editing 
LDFLAGS = -L D:\projetC\popTube\lib -L 'C:\Program Files (x86)\MySQL\MySQL Connector C 6.1\lib'

LDLIBS = -lmingw32 -lSDL2main -lSDL2  -lmysql
# curent variable for executable 
EXEC=main

all: 
	$(CC) $(CFLAGS) $(S_DIR)\main.c -o $(EXEC) $(LDFLAGS) $(CPPFLAGS)  $(LDLIBS)
	
#hello: main.o main.o
#	$(CC) -o hello hello.o main.o $(LDFLAGS)

#hello.o: hello.c
#	$(CC) -o hello.o -c hello.c $(CFLAGS)

#main.o: main.c hello.h
#	$(CC) -o main.o -c main.c $(CFLAGS)

#clean:
#	rm -rf *.o

mrproper : clean
	del main