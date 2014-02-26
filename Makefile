ifeq ($(OS),Windows_NT)
  CC = g++
  SDL_DLL = SDL2.dll
  SDL_INCLUDES = -I/usr/local/include/SDL2 -I/usr/include/mingw -Dmain=SDL_main
  SDL_LIBS = -L/usr/local/lib -lcygwin -lSDL2main -lSDL2 -mwindows -lfreetype -llibSDL2_ttf
  OPENGL_LIBS = -lopengl32
  ZIP = 7z
  ZIPFLAGS = a -tzip
  MAINFUNC = WinMain
else
  OPENGL_LIBS = -lgl -lglu
  MAINFUNC = SDL_main
  MAIN_LIB = -lSDL2main
endif

DEBUGFLAGS = -g -DDEBUG
RELEASEFLAGS = -O3
LDFLAGS = $(SDL_LIBS) $(OPENGL_LIBS)
INCLUDES = $(SDL_INCLUDES)
SOURCES = Tetris.cpp TEvent.cpp Tetrino.cpp TField.cpp TCell.cpp RGBColor.cpp TGameTimer.cpp
HEADERS = Tetris.hpp TEvent.hpp Tetrino.hpp TField.hpp TCell.hpp RGBColor.hpp TGameTimer.hpp
OBJECTS = Tetris.o TEvent.o Tetrino.o TField.o TCell.o RGBColor.o TGameTimer.o
TARGET ?= debug

ifeq ($(TARGET),debug)
  CFLAGS := $(CFLAGS) $(DEBUGFLAGS)
else ifeq ($(TARGET),release)
  CFLAGS := $(CFLAGS) $(RELEASEFLAGS)
else
  $(error "Unknown build target!")
endif

all: $(OBJECTS) tetris

zip: tetris.exe
	$(ZIP) $(ZIPFLAGS) Tetris.zip tetris.exe $(SDL_DLL)

$(OBJECTS): %.o: %.cpp %.hpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -std=c++0x $< -o $@


tetris: $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -static-libstdc++ -static-libgcc -o $@

.PHONY:
run: tetris
	./tetris

.PHONY:
clean:
	rm -f *.o tetris.exe tetris.exe.stackdump tetris.zip *.log

.PHONY:
prune:
	rm -f *~

.PHONY:
realclean: clean prune
