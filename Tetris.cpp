#include <iostream>
#include "Tetris.hpp"

Tetris::Tetris() {
  surf_display = NULL;
  resolution_x = 800;
  resolution_y = 600;
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

  // Debug since we're not spawning them throughout the game, yet
  for (int i = 0; i < 7; i++) {
    Tetrino *tetrino = new Tetrino();
    tetrino->OnLoad(i);
    tetrino->SetLocation(50 + 100 * i, 160);
    tetrinos.push_back(tetrino);
  }
  // End debug

  return true;
}

void Tetris::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
}

void Tetris::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
#ifdef DEBUG
  std::cout << "Key pressed: " << mod << " + " << sym << std::endl;
#endif

  // Quit if we pressed ESC
  if (mod == 0 && sym == 27) OnExit();

  if (sym != 304) {
    if (mod == 0)
      for (int i = 0; i < tetrinos.size(); i++)
	tetrinos[i]->RotateRight();
    else if (mod == 1)
      for (int i = 0; i < tetrinos.size(); i++)
	tetrinos[i]->RotateLeft();
  }
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glPushMatrix();

  for (int i = 0; i < tetrinos.size(); i++) {
    if (!tetrinos[i]) continue;
    tetrinos[i]->OnRender();
  }

  glPopMatrix();

  SDL_GL_SwapBuffers();
}

void Tetris::OnCleanup() {
 for (int i = 0; i < tetrinos.size(); i++) {
    if (!tetrinos[i]) continue;
    tetrinos[i]->OnCleanup();
    delete tetrinos[i];
  }

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

