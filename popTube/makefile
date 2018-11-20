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
CFLAGS=-W -Wall -ansi -pedantic -std=c99 

#LDFLAGS current variable for link editing 
LDFLAGS = -L $(P_DIR)\popTube\lib -L 'C:\Program Files (x86)\MySQL\MySQL Connector C 6.1\lib'

LDLIBS = -lmingw32 -lSDL2main -lSDL2  -lmysql
# curent variable for executable 
EXEC=main

all: $(EXEC)

$(EXEC): fileReader.o main.o
	$(CC) $(CFLAGS) -o	$(EXEC) fileReader.o main.o  $(LDFLAGS) $(CPPFLAGS)  $(LDLIBS)

main.o: $(P_DIR)\$(S_DIR)\main.c $(P_DIR)\$(H_DIR)\fileReader.h $(P_DIR)\$(H_DIR)\structures.h 
	$(CC)  -o main.o -c $(P_DIR)\$(S_DIR)\main.c $(CFLAGS) $(CPPFLAGS) 

#structure.o: $(P_DIR)\$(H_DIR)\structure.h $(P_DIR)\$(S_DIR)\structures.c


fileReader.o: $(P_DIR)\$(S_DIR)\fileReader.c $(P_DIR)\$(H_DIR)\fileReader.h $(P_DIR)\$(H_DIR)\structures.h 
	$(CC)   -o fileReader.o -c $(P_DIR)\$(S_DIR)\fileReader.c $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf *.o

