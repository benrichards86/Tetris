CC = g++-3
CFLAGS = -g
LIBS = -lSDL -lSDLmain
SOURCES = Tetris.cpp TEvent.cpp TSurface.cpp Tetrino.cpp
HEADERS = Tetris.h TEvent.h TSurface.h Tetrino.h

all: tetris

tetris: $(HEADERS) $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LIBS) -o $@

.PHONY:
clean:
	rm -f tetris.exe tetris.exe.stackdump

.PHONY:
prune:
	rm -f *~

.PHONY:
realclean: clean prune
