#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <GL/glu.h>
#include <GL/gl.h>
#include "TField.hpp"
#include "Tetrino.hpp"
#include "TCell.hpp"
#include "RGBColor.hpp"

using namespace tetris;

TField::TField() {
  x = 145;
  y = 80;
  current_tetrino = NULL;
  width = FIELD_WIDTH;
  height = FIELD_HEIGHT;
  for (int r = 0; r < height; r++)
    for (int c = 0; c < width; c++)
      field[r][c] = NULL;
}

TField::~TField() {
}

// Adds a piece to the field, dropped in place
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
      if (curr->row >= 0 && curr->row < height && curr->column >= 0 && curr->column < width) {
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
    if (row >= 0 && row < height && column >= 0 && column < width) {
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
  current_tetrino = next_tetrino;
  current_tetrino->row = 0;
  current_tetrino->column = (int)(width / 2) - 2;

  next_tetrino = new Tetrino;
  next_tetrino->OnLoad(rand() % 7);
  next_tetrino->row = 0;
  next_tetrino->column = 0;
}

// Drops a tetrino in place into the field. Returns true on success, false on fail.
bool TField::DropCurrentTetrino() {
  if (current_tetrino == NULL)
    return false;

  bool success = Add(current_tetrino);
  if (success)
    current_tetrino = NULL;
  return success;
}

void TField::OnInit() {
  srand(time(NULL)); // Initialize random number generator using system clock
  next_tetrino = new Tetrino; // Next piece to play
  next_tetrino->OnLoad(rand() % 7); // Randomly choose which piece

  // Delete animation 
  clear_line_hilight = RGBColor::WHITE;
  del_animation_complete = false;
  clearlines_timer.timer_rate = TGameTimer::ONE_SECOND / 4;
  clearlines_timer.loop_mode = TGameTimer::REPEATCOUNT;
  clearlines_timer.max_repeat_count = 5;

  // Timer function for line clear animation
  auto clearlines_delay_callback = [&] {
#ifdef DEBUG
    std::cout << "Animating" << std::endl;
#endif

    // Even frames flash
    enable_hilight = (clearlines_timer.RepeatCount() % 2 == 0) ? true : false;
    
    if (clearlines_timer.RepeatCount() == 1)
      del_animation_complete = true;
  };

  clearlines_timer.SetCallback(clearlines_delay_callback);
  clearlines_timer.enabled = false;
}

void TField::OnLoop() {
  for (int i = 0; i < field_cells.size(); i++)
    field_cells[i]->OnLoop();

  if (current_tetrino != NULL) {
    current_tetrino->OnLoop();
  }

  clearlines_timer.OnLoop();

  if (deleted_rows.empty()) {
    // Check for full rows and delete any that are found
    for (int r = height - 1; r >= 0; r--) {
      bool row_full = true;
      for (int c = 0; c < width; c++) {
        row_full = row_full && (field[r][c] != NULL);
      }

      // Mark full row as to delete
      if (row_full) {
        deleted_rows.push_back(r);
      }
    }
  }

  // Give time to animate deleted rows before deleting them.
  // Set timer to length of animation. Return from this method here until timer completes and don't allow a new piece to be spawned.
  if (!deleted_rows.empty()) {
    if (!del_animation_complete) {
      if (!clearlines_timer.enabled) {
        clearlines_timer.ResetTimer();
        clearlines_timer.enabled = true;
      }

      return;
    }
    else
      del_animation_complete = false;

    // Now, delete rows and shift blocks above deleted rows. Does it in one pass.
    // If on row to delete, delete it.
    // Else, shift blocks in row down by the number of rows we've deleted so far.
    for (int del_row_num = 0; del_row_num < deleted_rows.size(); del_row_num++) {
#ifdef DEBUG
      std::cout << "Deleted row: " << deleted_rows[del_row_num] << std::endl;
#endif
      int r = deleted_rows[del_row_num];
      while(r >= 0 && (del_row_num + 1 == deleted_rows.size() || r > deleted_rows[del_row_num + 1])) {
#ifdef DEBUG
        std::cout << "Shifting row: " << r << " by " << del_row_num + 1 << " rows." << std::endl;
#endif
        if (r == deleted_rows[del_row_num]) {
          for (int c = 0; c < width; c++) {
            delete field[r][c];
            field[r][c] = NULL;
          }
        }
        else {
          for (int c = 0; c < width; c++) {
            if (field[r][c] != NULL) {
              field[r][c]->row += del_row_num + 1;
              field[r + del_row_num + 1][c] = field[r][c];
              field[r][c] = NULL;
            }
          }
        }
        r--;
      }
    }

    // Clear out log of deleted rows now that they're deleted
    deleted_rows.clear();
  }

}

// Link in external color functions
extern void t_glColor3ubRGB(RGBColor color);
extern void t_glColor4ubRGB(RGBColor color, GLubyte alpha);

void TField::OnRender() {
  glPushMatrix();
  glTranslated(x, y, 0);
  glColor3ub(255, 255, 255);
  glBegin(GL_LINE_LOOP);
  glVertex3i(-40, -40, 1);
  glVertex3i(width * 20 - 40, -40, 1);
  glVertex3i(width * 20 - 40, height * 20 - 40, 1);
  glVertex3i(-40, height * 20 - 40, 1);
  glEnd();

  // Loop through all grid positions and render cells
  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++) {
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

  // Render row hilights
  if (enable_hilight) {
    for (int i = 0; i < deleted_rows.size(); i++) {
      t_glColor3ubRGB(clear_line_hilight);
      glPushMatrix();
      glBegin(GL_QUADS);
      glVertex3i(-40, 20 * deleted_rows[i] - 40, 0);
      glVertex3i(width * 20 - 40, 20 * deleted_rows[i] - 40, 0);
      glVertex3i(width * 20 - 40, 20 * deleted_rows[i] - 20, 0);
      glVertex3i(-40, 20 * deleted_rows[i] - 20, 0);
      glEnd();
      glPopMatrix();
    }
  }

  if (current_tetrino != NULL)
    current_tetrino->OnRender();

  if (next_tetrino != NULL) {
    glPushMatrix();
    glTranslated(500, 80, 0);
    next_tetrino->OnRender();
    glPopMatrix();
  }

  glPopMatrix();
}

void TField::OnCleanup() {
  delete current_tetrino;
}
