#include <iostream>
#include "Tetris.h"

Tetris::Tetris() {
  surf_display = NULL;
  surf_tetris = NULL;
  resolution_x = 800;
  resolution_y = 600;
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

  if ((surf_display = SDL_SetVideoMode(resolution_x, resolution_y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }

  if ((surf_tetris = SDL_CreateRGBSurface(0, resolution_x, resolution_y, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff)) == NULL) {
    return false;
  }

  // Debug since we're not spawning them throughout the game, yet
  for (int i = 0; i < 6; i++) {
    Tetrino *tetrino = new Tetrino();
    tetrino->OnLoad(i);
    tetrino->SetLocation(10 + 100 * i, 10);
    tetrinos.push_back(tetrino);
  }
    
  // End debug

  return true;
}

void Tetris::OnEvent(SDL_Event* event) {
  TEvent::OnEvent(event);
}

void Tetris::OnExit() {
  running = false;
}

void Tetris::OnLoop() {
  for (int i = 0; i < tetrinos.size(); i++) {
    if (!tetrinos[i]) continue;
    tetrinos[i]->OnLoop();
  }
}

void Tetris::OnRender() {
  for (int i = 0; i < tetrinos.size(); i++) {
    if (!tetrinos[i]) continue;
    tetrinos[i]->OnRender(surf_display);
  }

  TSurface::OnDraw(surf_display, surf_tetris, 0, 0);
  SDL_Flip(surf_display);
}

void Tetris::OnCleanup() {
  for (int i = 0; i < tetrinos.size(); i++) {
    if (!tetrinos[i]) continue;
    tetrinos[i]->OnCleanup();
    delete tetrinos[i];
  }

  SDL_FreeSurface(surf_tetris);
  SDL_FreeSurface(surf_display);
  SDL_Quit();
}


int main(int argc, char** argv) {
  Tetris game;

  return game.OnExecute();
}
