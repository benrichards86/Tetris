#include <iostream>

#if defined _WIN32 || defined __CYGWIN__
#include <windows.h>
#include "SDL.h"
#else
#include <SDL/SDL.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "Tetris.hpp"

using namespace tetris;

Tetris::Tetris() {
  surf_display = NULL;

#if 1
  resolution_x = 1024;
  resolution_y = 768;
  fullscreen = false;
#else
  resolution_x = 1920;
  resolution_y = 1080;
  fullscreen = true;
#endif

  scale = 20;
  level = 0;
  events_toggle = 0;

  running = true;
}

bool Tetris::SetDisplayMode(int res_x, int res_y, int bpp, bool fullscreen_mode) {
#ifdef DEBUG
  std::cout << "Switching to display mode: " << res_x << "x" << res_y << "x" << bpp << " [" << (fullscreen_mode ? "fullscreen" : "windowed") << "]" << std::endl;
#endif

  fullscreen = fullscreen_mode;

  if (fullscreen_mode)
    surf_display = SDL_SetVideoMode(0, 0, bpp, SDL_HWSURFACE | SDL_OPENGL | SDL_FULLSCREEN);
  else 
    surf_display = SDL_SetVideoMode(resolution_x, resolution_y, bpp, SDL_HWSURFACE | SDL_OPENGL);
     
  if (surf_display == NULL) {
    std::cerr << "Error switching " << (fullscreen_mode ? "into" : "out of") << " full screen mode!" << std::endl;
    return false;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  return true;
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

  if (!SetDisplayMode(resolution_x, resolution_y, 32, fullscreen))
    return false;

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

  game_timer.SetCurrentLevel(0);

  // Register the callback function for the game events
  auto tetris_timer_events = [&] {
    Tetrino *curr = play_field.current_tetrino;
    if (curr) {
      curr->MoveDown();
      if (play_field.CheckIfIntersect(play_field.current_tetrino)) {
	curr->MoveUp();
	if (!play_field.DropCurrentTetrino()) {
	  // game over
	  std::cout << "Game over!" << std::endl;
	  game_timer.enabled = false;
	}
      }
    }
    else {
      play_field.SpawnTetrino();
    }
  };

  game_timer.SetCallback(tetris_timer_events);
  
  return true;
}

void Tetris::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
#ifdef DEBUG
  std::cout << "Key released: " << mod << " + " << sym << " [" << unicode << "]" <<  std::endl;
#endif

  // Handle other keyboard events
  if (sym == SDLK_LEFT) {
    events_toggle &= ~0x1;
  }

  if (sym == SDLK_RIGHT) {
    events_toggle &= ~0x2;
  }

  if (sym == SDLK_UP) {
    events_toggle &= ~0x4;
  }

  if (sym == SDLK_DOWN) {
    events_toggle &= ~0x8;
  }

  if (sym == SDLK_z) {
    events_toggle &= ~0x10;
  }

  if (sym == SDLK_x) {
    events_toggle &= ~0x20;
  }
}

void Tetris::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
#ifdef DEBUG
  std::cout << "Key pressed: " << mod << " + " << sym << " [" << unicode << "]" <<  std::endl;
#endif

  // Alt+Enter to switch between fullscreen & windowed mode
  if ((mod == KMOD_LALT || mod == KMOD_RALT) && sym == SDLK_RETURN) {
    if (!SetDisplayMode(resolution_x, resolution_y, 32, !fullscreen))
      OnExit();
  }

  // Quit if we pressed ESC
  if (sym == SDLK_ESCAPE) {
    OnExit();
  }

  // Handle other keyboard events
  if (sym == SDLK_LEFT) {
    events_toggle |= 0x1;
  }

  if (sym == SDLK_RIGHT) {
    events_toggle |= 0x2;
  }

  if (sym == SDLK_UP) {
    events_toggle |= 0x4;
  }

  if (sym == SDLK_DOWN) {
    events_toggle |= 0x8;
  }

  if (sym == SDLK_z) {
    events_toggle |= 0x10;
  }

  if (sym == SDLK_x) {
    events_toggle |= 0x20;
  }
}

void Tetris::OnEvent(SDL_Event* event) {
  TEvent::OnEvent(event);
}

void Tetris::OnExit() {
  running = false;
}

void Tetris::OnLoop() {
  // Handle other keyboard events
  if (events_toggle & 0x1) { // move left
    if (play_field.current_tetrino != NULL) {
      play_field.current_tetrino->MoveLeft();
      if (play_field.CheckIfIntersect(play_field.current_tetrino))
	play_field.current_tetrino->MoveRight();
    }
  }

  if (events_toggle & 0x2) { // move right
    if (play_field.current_tetrino != NULL) {
      play_field.current_tetrino->MoveRight();
      if (play_field.CheckIfIntersect(play_field.current_tetrino))
	play_field.current_tetrino->MoveLeft();
    }
  }

  if (events_toggle & 0x4) { // move up
    if (play_field.current_tetrino != NULL) {
      play_field.current_tetrino->MoveUp();
      if (play_field.CheckIfIntersect(play_field.current_tetrino))
	play_field.current_tetrino->MoveDown();
    }
  }

  if (events_toggle & 0x8) { // move down
    if (play_field.current_tetrino != NULL) {
      play_field.current_tetrino->MoveDown();
      if (play_field.CheckIfIntersect(play_field.current_tetrino))
	play_field.current_tetrino->MoveUp();
    }
  }

  if (events_toggle & 0x10) { // rotate left
    if (play_field.current_tetrino != NULL) {
      play_field.current_tetrino->RotateRight();
      if (play_field.CheckIfIntersect(play_field.current_tetrino))
	play_field.current_tetrino->RotateLeft();
    }
  }

  if (events_toggle & 0x20) { // rotate left
    if (play_field.current_tetrino != NULL) {
      play_field.current_tetrino->RotateLeft();
      if (play_field.CheckIfIntersect(play_field.current_tetrino))
	play_field.current_tetrino->RotateRight();
    }
  }


  game_timer.OnLoop();
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
#ifdef DEBUG
  std::cout << lpCmdLine << ", " << nCmdShow << std::endl;
#endif
  Tetris game;
  return game.OnExecute();
}
#endif

