ifeq ($(OS),Windows_NT)
  PLATFORM_LIBS = -mno-cygwin -mwindows
  OPENGL_LIBS = -lopengl32
  SDL_INCLUDES = -I/usr/include/SDL
  SDL_LIBS = -L/usr/local/lib
  ZIP = 7z
  ZIPFLAGS = a -tzip
else
  OPENGL_LIBS = -lgl
endif

SDL_LIBS = -lSDL -lSDLmain
CC = g++-3
DEBUGFLAGS = -g -DDEBUG
RELEASEFLAGS = -O3
LIBS = $(OPENGL_LIBS) $(PLATFORM_LIBS) $(SDL_LIBS)
INCLUDES = $(SDL_INCLUDES)
SOURCES = Tetris.cpp TEvent.cpp Tetrino.cpp
HEADERS = Tetris.h TEvent.h Tetrino.h

all: tetris

zip: tetris.exe SDL.dll
	$(ZIP) $(ZIPFLAGS) Tetris.zip tetris.exe SDL.dll

tetris: $(HEADERS) $(SOURCES)
ifndef RELEASE
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(LIBS) -o $@
else
	$(CC) $(SOURCES) $(CFLAGS) $(RELEASEFLAGS) $(INCLUDES) $(LIBS) -o $@
endif

.PHONY:
run: tetris
	./tetris

.PHONY:
clean:
	rm -f tetris.exe tetris.exe.stackdump

.PHONY:
prune:
	rm -f *~

.PHONY:
realclean: clean prune
