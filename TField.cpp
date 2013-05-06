#include "TField.hpp"
#include "Tetrino.hpp"

using namespace tetris;

TField::TField() {
  field = new int[10][12];
}

TField::~TField() {
  delete field;
}

bool TField::Add(Tetrino t) {
  if (CheckIntersect(t)) {
    
  }
}

bool TField::CheckIntersect(Tetrino t) {
  return true;
}
