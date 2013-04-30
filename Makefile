ifeq ($(OS),Windows_NT)
  PLATFORM_LIBS = -mno-cygwin -mwindows
  OPENGL_LIBS = -lopengl32
  SDL_INCLUDES = -I/usr/include/SDL
  SDL_LIBS = -L/usr/local/lib
else
  OPENGL_LIBS = -lgl
endif

SDL_LIBS = -lSDL -lSDLmain
CC = g++-3
CFLAGS = -g
LIBS = $(OPENGL_LIBS) $(PLATFORM_LIBS) $(SDL_LIBS)
INCLUDES = $(SDL_INCLUDES)
SOURCES = Tetris.cpp TEvent.cpp Tetrino.cpp
HEADERS = Tetris.h TEvent.h Tetrino.h

all: tetris

tetris: $(HEADERS) $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(INCLUDES) $(LIBS) -o $@

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
