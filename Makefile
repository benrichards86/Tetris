CC = g++-3
CFLAGS = -g
LIBS = -lSDL -lSDLmain
SOURCES = Tetris.cpp TEvent.cpp TSurface.cpp
HEADERS = Tetris.h TEvent.h TSurface.h

all: tetris

tetris: $(HEADERS) $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LIBS) -o $@

.PHONY:
clean:
	rm -f tetris.exe

.PHONY:
prune:
	rm -f *~

.PHONY:
realclean: clean prune
