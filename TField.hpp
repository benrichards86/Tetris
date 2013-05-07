// TField: The playing field where the tetrinos collect

#ifndef TFIELD_HPP
#define TFIELD_HPP

#include <vector>
#include "Tetrino.hpp"
#include "TCell.hpp"

#define FIELD_WIDTH 20
#define FIELD_HEIGHT 32

namespace tetris {

class TField {
public:
  TField();
  ~TField();
  
public:
  bool Add(Tetrino *t);
  void OnLoop();
  void OnRender();
  void OnCleanup();

public:
  bool CheckIfIntersect(Tetrino *t);
  bool StartTetrino(Tetrino *t);
  
private:
  std::vector<TCell*> field_cells;
  TCell* field[FIELD_HEIGHT][FIELD_WIDTH];

public:
  Tetrino *current_tetrino;
  int x;
  int y;

};

}

#endif
