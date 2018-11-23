#CC current variable for compiler in C 
CC=gcc

#Project DIR 
P_DIR=C:\projetC
#Source DIR
S_DIR=popTube\src
#Header DIR
H_DIR=popTube\include

CPPFLAGS = -I $(P_DIR)\$(H_DIR) -I 'C:\Program Files (x86)\MySQL\MySQL Connector C 6.1\include'


#CFLAGS current variable for compilation options   
#-W et -Wall display front end compiler warnings 
#-ansi request ansi compilation 
#-pedantic display compiler warnings 
CFLAGS=-W -Wall -ansi -pedantic -std=c99 -g

#LDFLAGS current variable for link editing 
LDFLAGS = -L $(P_DIR)\popTube\lib -L 'C:\Program Files (x86)\MySQL\MySQL Connector C 6.1\lib'

LDLIBS = -lmingw32 -lSDL2main -lSDL2  -lmysql
# curent variable for executable 
EXEC=main

all: $(EXEC)

$(EXEC): fileManager.o structures.o main.o 
	$(CC) $(CFLAGS) -o	$(EXEC) fileManager.o structures.o  main.o  $(LDFLAGS) $(CPPFLAGS)  $(LDLIBS)

main.o: $(P_DIR)\$(S_DIR)\main.c $(P_DIR)\$(H_DIR)\fileManager.h $(P_DIR)\$(H_DIR)\structures.h 
	$(CC)  -o main.o -c $(P_DIR)\$(S_DIR)\main.c $(CFLAGS) $(CPPFLAGS) 

structures.o: $(P_DIR)\$(H_DIR)\structures.h $(P_DIR)\$(S_DIR)\structures.c
	$(CC)   -o structures.o -c $(P_DIR)\$(S_DIR)\structures.c $(CFLAGS) $(CPPFLAGS)

fileManager.o: $(P_DIR)\$(S_DIR)\fileManager.c $(P_DIR)\$(H_DIR)\fileManager.h $(P_DIR)\$(H_DIR)\structures.h 
	$(CC)   -o fileManager.o -c $(P_DIR)\$(S_DIR)\fileManager.c $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf *.o

