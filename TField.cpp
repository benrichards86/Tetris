#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <GL/glu.h>
#include <GL/gl.h>
#include "TField.hpp"
#include "Tetrino.hpp"
#include "TCell.hpp"

using namespace tetris;

TField::TField() {
  x = 145;
  y = 80;
  current_tetrino = NULL;
  for (int r = 0; r < FIELD_HEIGHT; r++)
    for (int c = 0; c < FIELD_WIDTH; c++)
      field[r][c] = NULL;


  srand(time(NULL));
}

TField::~TField() {
}

bool TField::Add(Tetrino *t) {
  if (CheckIfIntersect(t) == false) {
    for (int i = 0; i < 4; i++) {
      TCell *curr = (*t)[i];
#ifdef DEBUG
      std::cout << "t -> row:" << t->row << ", column:" << t->column << std::endl;
      std::cout << "curr -> row:" << curr->row << ", column:" << curr->column << std::endl;
#endif
      curr->row +=  t->row;
      curr->column += t->column;
      if (curr->row >= 0 && curr->row < FIELD_HEIGHT && curr->column >= 0 && curr->column < FIELD_WIDTH) {
        field_cells.push_back(curr);
        field[curr->row][curr->column] = curr;
#ifdef DEBUG
        std::cout << "Dropping cell at row:" << curr->row << ", column:" << curr->column << std::endl;
#endif
      }
    }
  }
  else {
#ifdef DEBUG
    std::cout << "Cannot drop here! Intersection with existing cells!" << std::endl;
#endif
    return false;
  }

  return true;
}

// Checks if the tetrino would intersect any cells in the playing field.
// Returns false if no intersections
// Returns true if exist intersections
bool TField::CheckIfIntersect(Tetrino *t) {
  for (int i = 0; i < 4; i++) {
    TCell *curr = (*t)[i];
    int row = t->row + curr->row;
    int column = t->column + curr->column;
    if (row >= 0 && row < FIELD_HEIGHT && column >= 0 && column < FIELD_WIDTH) {
      if (field[row][column] != NULL)
        return true;
    }
    else {
      return true;
    }
  }

  return false;
}

// Spawn a new tetrino
void TField::SpawnTetrino() {
  current_tetrino = new Tetrino;
  current_tetrino->OnLoad(rand() % 7);
  current_tetrino->row = 0;
  current_tetrino->column = (int)(FIELD_WIDTH / 2) - 2;
}

// Drops a tetrino in place into the field
bool TField::DropCurrentTetrino() {
  if (current_tetrino == NULL)
    return false;

  bool success = Add(current_tetrino);
  if (success)
    current_tetrino = NULL;
  return success;
}

void TField::OnLoop() {
  for (int i = 0; i < field_cells.size(); i++)
    field_cells[i]->OnLoop();

  if (current_tetrino != NULL) {
    current_tetrino->OnLoop();
  }

  // Check for full rows and delete any that are found
  std::vector<int> deleted_rows;
  for (int r = FIELD_HEIGHT - 1; r >= 0; r--) {
    bool row_full = true;
    for (int c = 0; c < FIELD_WIDTH; c++) {
      row_full = row_full && (field[r][c] != NULL);
    }

    if (row_full) {
      for (int c = 0; c < FIELD_WIDTH; c++) {
	delete field[r][c];
	field[r][c] = NULL;
      }

      deleted_rows.push_back(r);
    }
  }

  for (int del_row_num = 0; del_row_num < deleted_rows.size(); del_row_num++) {
#ifdef DEBUG
    std::cout << "Deleted row: " << deleted_rows[del_row_num] << std::endl;
#endif
    int r = deleted_rows[del_row_num];
    while(r >= 0 && (del_row_num + 1 == deleted_rows.size() || r > deleted_rows[del_row_num + 1])) {
#ifdef DEBUG
      std::cout << "Shifting row: " << r << " by " << del_row_num + 1 << " rows." << std::endl;
#endif
      for (int c = 0; c < FIELD_WIDTH; c++) {
	if (field[r][c] != NULL) {
	  field[r][c]->row += del_row_num + 1;
	  field[r + del_row_num + 1][c] = field[r][c];
	  field[r][c] = NULL;
	}
      }
      r--;
    }
  }
}

void TField::OnRender() {
  glPushMatrix();
  glTranslated(x, y, 0);
  glColor3ub(255, 255, 255);
  glBegin(GL_LINE_LOOP);
  glVertex3i(-40, -40, 1);
  glVertex3i(FIELD_WIDTH * 20 - 40, -40, 1);
  glVertex3i(FIELD_WIDTH * 20 - 40, FIELD_HEIGHT * 20 - 40, 1);
  glVertex3i(-40, FIELD_HEIGHT * 20 - 40, 1);
  glEnd();

  for (int r = 0; r < FIELD_HEIGHT; r++) {
    for (int c = 0; c < FIELD_WIDTH; c++) {
      if (field[r][c] != NULL)
        field[r][c]->OnRender();
#ifdef DEBUG
      else {
        glColor3ub(127, 127, 127);
        glPushMatrix();
        glLineStipple(2, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINE_LOOP);
        glVertex3i(20 * c - 40, 20 * r - 40, 0);
        glVertex3i(20 * c - 20, 20 * r - 40, 0);
        glVertex3i(20 * c - 20, 20 * r - 20, 0);
        glVertex3i(20 * c - 40, 20 * r - 20, 0);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glPopMatrix();
      }
#endif
    }
  }
  
  if (current_tetrino != NULL)
    current_tetrino->OnRender();

  glPopMatrix();
}

void TField::OnCleanup() {
  delete current_tetrino;
}
