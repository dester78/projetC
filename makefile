#CC current variable for compiler in C 
CC=gcc


#Source DIR
S_DIR=src
#Header DIR 
H_DIR=include

L_DIR=lib

CPPFLAGS = -I $(H_DIR)/ -I $(H_DIR)/SDL2  -I $(H_DIR)/MYSQL

#CFLAGS current variable for compilation options   
#-W et -Wall display front end compiler warnings 
#-ansi request ansi compilation 
#-pedantic display compiler warnings 
CFLAGS=-W -Wall -ansi -pedantic -std=c99 

#LDFLAGS current variable for link editing 
LDFLAGS = -L $(L_DIR)/SDL2 -L $(L_DIR)/MYSQL

LDLIBS = -lmingw32 -lSDL2main -lSDL2  -lSDL2_ttf -lSDL2_image -lmysql 
# curent variable for executable 
EXEC=main

all: $(EXEC)

$(EXEC): dbManager.o  fileManager.o structures.o SDLColor.o SDLMain.o main.o formatString.o SDLConfigStructures.o SDLObjectsStructures.o SDLObjects.o SDLDraw.o  mathCalculation.o SDLGUIObjects.o SDLRectPoint.o SDLBackgroundObjects.o SDLMetroLine.o SDLTimer.o SDLMetroStation.o SDLTransport.o
	$(CC) $(CFLAGS) -o $(EXEC)  formatString.o fileManager.o structures.o dbManager.o SDLMain.o SDLConfigStructures.o  SDLObjectsStructures.o SDLObjects.o SDLDraw.o mathCalculation.o SDLGUIObjects.o SDLRectPoint.o SDLBackgroundObjects.o SDLColor.o main.o  SDLMetroLine.o SDLTimer.o SDLMetroStation.o SDLTransport.o $(LDFLAGS) $(CPPFLAGS)  $(LDLIBS)

main.o: $(S_DIR)/main.c $(H_DIR)/fileManager.h $(H_DIR)/structures.h $(H_DIR)/dbManager.h  $(H_DIR)/SDLConfigStructures.h $(H_DIR)/SDLObjects.h
	$(CC)  -o main.o -c $(S_DIR)/main.c $(CFLAGS) $(CPPFLAGS) 

SDLMain.o: $(H_DIR)/SDLmain.h $(S_DIR)/SDLmain.c $(H_DIR)/SDLColor.h  $(H_DIR)/structures.h  $(H_DIR)/SDLConfigStructures.h  $(H_DIR)/SDLObjectsStructures.h $(H_DIR)/SDLObjects.h $(H_DIR)/SDLDraw.h $(H_DIR)/SDLGUIObjects.h  $(H_DIR)/SDLMetroStation.h $(H_DIR)/SDLBackgroundObjects.h $(H_DIR)/SDLRectPoint.h $(H_DIR)/SDLTimer.h $(H_DIR)/SDLMetroLine.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLmain.o -c $(S_DIR)/SDLmain.c $(CFLAGS) $(CPPFLAGS)

dbManager.o: $(H_DIR)/dbManager.h $(S_DIR)/dbManager.c $(H_DIR)/structures.h  $(H_DIR)/fileManager.h 
	$(CC)   -o dbManager.o -c $(S_DIR)/dbManager.c $(CFLAGS) $(CPPFLAGS)

SDLObjects.o: $(H_DIR)/SDLObjects.h $(S_DIR)/SDLObjects.c  $(H_DIR)/SDLConfigStructures.h  $(H_DIR)/SDLObjectsStructures.h  $(H_DIR)/fileManager.h 
	$(CC)   -o SDLObjects.o -c $(S_DIR)/SDLObjects.c $(CFLAGS) $(CPPFLAGS)

SDLBackgroundObjects.o: $(H_DIR)/SDLBackgroundObjects.h $(S_DIR)/SDLBackgroundObjects.c $(H_DIR)/SDLObjectsStructures.h  $(H_DIR)/SDLRectPoint.h  $(H_DIR)/SDLGUIObjects.h  $(H_DIR)/mathCalculation.h  $(H_DIR)/SDLColor.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLBackgroundObjects.o -c $(S_DIR)/SDLBackgroundObjects.c $(CFLAGS) $(CPPFLAGS)

SDLMetroStation.o: $(H_DIR)/SDLMetroStation.h $(S_DIR)/SDLMetroStation.c $(H_DIR)/SDLBackgroundObjects.h $(H_DIR)/SDLObjectsStructures.h  $(H_DIR)/SDLRectPoint.h  $(H_DIR)/SDLGUIObjects.h  $(H_DIR)/mathCalculation.h  $(H_DIR)/SDLColor.h $(H_DIR)/SDLMetroLine.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLMetroStation.o -c $(S_DIR)/SDLMetroStation.c $(CFLAGS) $(CPPFLAGS)


SDLTransport.o: $(H_DIR)/SDLTransport.h $(S_DIR)/SDLTransport.c $(H_DIR)/SDLBackgroundObjects.h $(H_DIR)/SDLObjectsStructures.h  $(H_DIR)/SDLRectPoint.h  $(H_DIR)/SDLGUIObjects.h  $(H_DIR)/mathCalculation.h  $(H_DIR)/SDLColor.h $(H_DIR)/SDLMetroLine.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLTransport.o -c $(S_DIR)/SDLTransport.c $(CFLAGS) $(CPPFLAGS)

SDLGUIObjects.o: $(H_DIR)/SDLGUIObjects.h $(S_DIR)/SDLGUIObjects.c  $(H_DIR)/SDLObjectsStructures.h $(H_DIR)/SDLColor.h $(H_DIR)/SDLDraw.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLGUIObjects.o -c $(S_DIR)/SDLGUIObjects.c $(CFLAGS) $(CPPFLAGS)

SDLConfigStructures.o: $(H_DIR)/SDLConfigStructures.h $(S_DIR)/SDLConfigStructures.c  $(H_DIR)/fileManager.h $(H_DIR)/formatString.h
	$(CC)   -o SDLConfigStructures.o -c $(S_DIR)/SDLConfigStructures.c $(CFLAGS) $(CPPFLAGS)

SDLObjectsStructures.o: $(H_DIR)/SDLObjectsStructures.h $(S_DIR)/SDLObjectsStructures.c $(H_DIR)/fileManager.h $(H_DIR)/SDLConfigStructures.h  $(H_DIR)/SDLColor.h   $(H_DIR)/SDLRectPoint.h  $(H_DIR)/mathCalculation.h  $(H_DIR)/SDLDraw.h $(H_DIR)/SDLColor.h
	$(CC)   -o SDLObjectsStructures.o -c $(S_DIR)/SDLObjectsStructures.c $(CFLAGS) $(CPPFLAGS)

structures.o: $(H_DIR)/structures.h $(S_DIR)/structures.c $(H_DIR)/fileManager.h $(H_DIR)/formatString.h 
	$(CC)   -o structures.o -c $(S_DIR)/structures.c $(CFLAGS) $(CPPFLAGS)

fileManager.o: $(S_DIR)/fileManager.c $(H_DIR)/fileManager.h $(H_DIR)/structures.h $(H_DIR)/formatString.h $(H_DIR)/SDLColor.h
	$(CC)   -o fileManager.o -c $(S_DIR)/fileManager.c $(CFLAGS) $(CPPFLAGS)

formatString.o: $(S_DIR)/formatString.c $(H_DIR)/formatString.h $(H_DIR)/fileManager.h 
	$(CC)   -o formatString.o -c $(S_DIR)/formatString.c $(CFLAGS) $(CPPFLAGS)

SDLColor.o: $(H_DIR)/SDLColor.h $(S_DIR)/SDLColor.c  $(H_DIR)/fileManager.h 
	$(CC)   -o SDLColor.o -c $(S_DIR)/SDLColor.c $(CFLAGS) $(CPPFLAGS)

SDLRectPoint.o: $(H_DIR)/SDLRectPoint.h $(S_DIR)/SDLRectPoint.c  $(H_DIR)/SDLObjectsStructures.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLRectPoint.o -c $(S_DIR)/SDLRectPoint.c $(CFLAGS) $(CPPFLAGS)

SDLMetroLine.o: $(H_DIR)/SDLMetroLine.h $(S_DIR)/SDLMetroLine.c $(H_DIR)/SDLRectPoint.h $(H_DIR)/SDLMetroStation.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLMetroLine.o -c $(S_DIR)/SDLMetroLine.c $(CFLAGS) $(CPPFLAGS)

SDLDraw.o: $(H_DIR)/SDLDraw.h $(S_DIR)/SDLDraw.c $(H_DIR)/SDLObjectsStructures.h $(H_DIR)/fileManager.h 
	$(CC)   -o SDLDraw.o -c $(S_DIR)/SDLDraw.c $(CFLAGS) $(CPPFLAGS)

SDLTimer.o: $(H_DIR)/SDLTimer.h $(S_DIR)/SDLTimer.c $(H_DIR)/SDLObjectsStructures.h $(H_DIR)/SDLMetroStation.h $(H_DIR)/SDLMetroLine.h $(H_DIR)/SDLTransport.h $(H_DIR)/fileManager.h  
	$(CC)   -o SDLTimer.o -c $(S_DIR)/SDLTimer.c $(CFLAGS) $(CPPFLAGS)

mathCalculation.o: $(H_DIR)/mathCalculation.h $(S_DIR)/mathCalculation.c $(H_DIR)/SDLObjectsStructures.h $(H_DIR)/fileManager.h 
	$(CC)   -o mathCalculation.o -c $(S_DIR)/mathCalculation.c $(CFLAGS) $(CPPFLAGS)

clean:
	rm *.o core

delproper: clean
	rm main.exe


