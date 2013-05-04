// TField: The playing field where the tetrinos collect

#ifndef TFIELD_HPP
#define TFIELD_HPP

#include "Tetrino.hpp"

class TField {
 public:
  TField();
  ~TField();

 public:
  bool add_new(Tetrino new_tetrino);

 private:
  int field[16][10];
};

#endif
