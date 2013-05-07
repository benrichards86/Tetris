#include <vector>
#include <GL/glu.h>
#include <GL/gl.h>
#include "TField.hpp"
#include "Tetrino.hpp"
#include "TCell.hpp"

using namespace tetris;

TField::TField() {
  x = 145;
  y = 30;
  current_tetrino = NULL;
  for (int r = 0; r < 16; r++)
    for (int c = 0; c < 10; c++)
      field[r][c] = NULL;
}

TField::~TField() {
}

bool TField::Add(Tetrino *t) {
  if (CheckIfIntersect(t)) {
    for (int i = 0; i < 4; i++) {
      field_cells.push_back((*t)[i]);
      field[t->row][t->column] = field_cells[field_cells.size() - 1];
    }
  }
}

// Checks if the tetrino would intersect any cells in the playing field.
// Returns false if no intersections
// Returns true if exist intersections
bool TField::CheckIfIntersect(Tetrino *t) {
  for (int i = 0; i < 4; i++) {
    if (field[t->row][t->column] != NULL)
      return true;
  }

  return false;
}

// Places a tetrino at the top and starts making it fall
bool TField::StartTetrino(Tetrino *t) {
  t->row = 2;
  t->column = (int)(FIELD_WIDTH / 2);
  current_tetrino = t;
}

void TField::OnLoop() {
  for (int i = 0; i < field_cells.size(); i++)
    field_cells[i]->OnLoop();

  if (current_tetrino != NULL) {
    current_tetrino->OnLoop();
  }
}

void TField::OnRender() {
  glPushMatrix();
  glTranslated(x, y, 0);
  glColor3ub(255, 255, 255);
  glBegin(GL_LINE_LOOP);
  glVertex3i(0, 0, 1);
  glVertex3i(FIELD_WIDTH * 20, 0, 1);
  glVertex3i(FIELD_WIDTH * 20, FIELD_HEIGHT * 20, 1);
  glVertex3i(0, FIELD_HEIGHT * 20, 1);
  glEnd();

  for (int i = 0; i < field_cells.size(); i++)
    field_cells[i]->OnRender();
  
  if (current_tetrino != NULL)
    current_tetrino->OnRender();

  glPopMatrix();
}

void TField::OnCleanup() {
  delete current_tetrino;
}
