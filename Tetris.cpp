#include "Tetris.h"

Tetris::Tetris() {
  surf_display = NULL;
  surf_tetris = NULL;
  running = true;
}

int Tetris::OnExecute() {
  if (OnInit() == false)
    return -1;

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

  if ((surf_display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  return true;
}

void Tetris::OnEvent(SDL_Event* event) {
  TEvent::OnEvent(event);
}

void Tetris::OnExit() {
  running = false;
}

void Tetris::OnLoop() {
}

void Tetris::OnRender() {
  TSurface::OnDraw(surf_display, surf_tetris, 0, 0);
  SDL_Flip(surf_display);
}

void Tetris::OnCleanup() {
  SDL_FreeSurface(surf_tetris);
  SDL_FreeSurface(surf_display);
  SDL_Quit();
}


int main(int argc, char** argv) {
  Tetris game;

  return game.OnExecute();
}
