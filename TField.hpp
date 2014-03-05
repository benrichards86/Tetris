// TField: The playing field where the tetrinos collect

#ifndef TFIELD_HPP
#define TFIELD_HPP

#include <vector>
#include "Tetrino.hpp"
#include "TCell.hpp"
#include "TGameTimer.hpp"
#include "RGBColor.hpp"

#define FIELD_WIDTH 16
#define FIELD_HEIGHT 24

namespace tetris {

class TField {
public:
  TField();
  ~TField();
  
public:
  bool Add(Tetrino *t);
  void OnInit();
  void OnLoop();
  void OnRender();
  void OnCleanup();

public:
  bool CheckIfIntersect(Tetrino *t);
  void SpawnTetrino();
  bool DropCurrentTetrino();
  
private:
  std::vector<TCell*> field_cells;
  TGameTimer clearlines_timer;
  std::vector<int> deleted_rows;
  bool del_animation_complete;
  bool enable_hilight;
  RGBColor clear_line_hilight;

public:
  TCell* field[FIELD_HEIGHT][FIELD_WIDTH];
  Tetrino *current_tetrino;
  Tetrino *next_tetrino;
  int x;
  int y;
  int width;
  int height;

};

}

#endif
