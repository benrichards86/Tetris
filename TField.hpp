// TField: The playing field where the tetrinos collect

#ifndef TFIELD_HPP
#define TFIELD_HPP

#include "Tetrino.hpp"
namespace tetris {

class TField {
public:
  TField();
  ~TField();
  
public:
  bool Add(Tetrino t);
  void OnLoop();
  
private:
  bool CheckIntersect(Tetrino t);
  
private:
  int (*field)[12];
};

}

#endif
