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
SOURCES = Tetris.cpp TEvent.cpp Tetrino.cpp TField.cpp TCell.cpp RGBColor.cpp
HEADERS = Tetris.hpp TEvent.hpp Tetrino.hpp TField.hpp TCell.hpp RGBColor.hpp
TARGET ?= debug

all: tetris

zip: tetris.exe SDL.dll
	$(ZIP) $(ZIPFLAGS) Tetris.zip tetris.exe SDL.dll

tetris: $(HEADERS) $(SOURCES)
ifeq ($(TARGET),debug)
	$(CC) $(SOURCES) $(CFLAGS) $(DEBUGFLAGS) $(INCLUDES) $(LIBS) -o $@
else ifeq ($(TARGET),release)
	$(CC) $(SOURCES) $(CFLAGS) $(RELEASEFLAGS) $(INCLUDES) $(LIBS) -o $@
else
	$(error "Unknown build target!")
endif

.PHONY:
run: tetris
	./tetris

.PHONY:
clean:
	rm -f tetris.exe tetris.exe.stackdump tetris.zip

.PHONY:
prune:
	rm -f *~

.PHONY:
realclean: clean prune
