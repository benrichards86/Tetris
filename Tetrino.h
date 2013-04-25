#include <vector>
#include "TSurface.h"

class Tetrino {
 protected:
  SDL_Surface *surf_entity;

 public:
  int x;
  int y;
  int type;

 public:
  Tetrino();
  virtual ~Tetrino();

 public:
  virtual bool OnLoad(int type);
  virtual void SetLocation(int x_loc, int y_loc);
  virtual void OnLoop();
  virtual void OnRender(SDL_Surface *surf_display);
  virtual void OnCleanup();
};

