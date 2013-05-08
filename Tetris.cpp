#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Tetris.hpp"

using namespace tetris;

Tetris::Tetris() {
  surf_display = NULL;
  resolution_x = 1024;
  resolution_y = 768;
  scale = 20;
  running = true;
}

int Tetris::OnExecute() {
  if (OnInit() == false)
    return -1;

  SDL_WM_SetCaption("Tetris Clone", 0); 

  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }

    OnLoop();
    OnRender();
  }

  OnCleanup();

  return 0;
}

bool Tetris::OnInit() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if ((surf_display = SDL_SetVideoMode(resolution_x, resolution_y, 32, SDL_HWSURFACE | SDL_OPENGL)) == NULL) {
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // OpenGL intitializations
  glClearColor(0, 0, 0, 0);
  glClearDepth(1.0f);
  glViewport(0, 0, resolution_x, resolution_y);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0, resolution_x, resolution_y, 0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();

  // This is how we start a tetrino in play
  srand(time(NULL));
  int type = rand() % 7;
  Tetrino *tetrino = new Tetrino;
  tetrino->OnLoad(type);
  play_field.StartTetrino(tetrino);

  return true;
}

void Tetris::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
}

void Tetris::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
#ifdef DEBUG
  std::cout << "Key pressed: " << mod << " + " << sym << " [" << unicode << "]" <<  std::endl;
#endif

  // Quit if we pressed ESC
  if (mod == 0) {
    switch(sym) {
    case 27: {
      OnExit();
      break;
    }
    case 276: {
      if (play_field.current_tetrino != NULL)
	play_field.current_tetrino->MoveLeft();
      break;
    }
    case 275: {
      if (play_field.current_tetrino != NULL)
	play_field.current_tetrino->MoveRight();
      break;
    }
    case 273: {
      if (play_field.current_tetrino != NULL)
	play_field.current_tetrino->MoveUp();
      break;
    }
    case 274: {
      if (play_field.current_tetrino != NULL)
	play_field.current_tetrino->MoveDown();
      break;
    }
    case 32: {
      if (play_field.DropCurrentTetrino()) {
	int type = rand() % 7;
	Tetrino *tetrino = new Tetrino;
	tetrino->OnLoad(type);
	play_field.StartTetrino(tetrino);
      }
      break;
    }
    default: {
      if (play_field.current_tetrino != NULL)
	play_field.current_tetrino->RotateRight();
      break;
    }
    }
  }
}

void Tetris::OnEvent(SDL_Event* event) {
  TEvent::OnEvent(event);
}

void Tetris::OnExit() {
  running = false;
}

void Tetris::OnLoop() {
  play_field.OnLoop();
}

void Tetris::OnRender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  play_field.OnRender();

  SDL_GL_SwapBuffers();
}

void Tetris::OnCleanup() {
  play_field.OnCleanup();

  SDL_FreeSurface(surf_display);
  SDL_Quit();
}

#ifndef _WIN32
int main(int argc, char** argv) {
  Tetris game;
  return game.OnExecute();
}
#else
int WinMain(HINSTANCE__* hInstance, HINSTANCE__* hPrevInstance, char* lpCmdLine, int nCmdShow) {
  Tetris game;
  return game.OnExecute();
}
#endif

