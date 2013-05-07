#include <GL/glu.h>
#include <GL/gl.h>
#include "RGBColor.hpp"
#include "TCell.hpp"

using namespace tetris;

TCell::TCell() {
  row = column = 0;
  rot = 0;
  color.red = color.green = color.blue = 255;
}

TCell::~TCell() {
}

bool TCell::OnLoad(int column_loc, int row_loc, int rotation, RGBColor base_color) {
  column = column_loc;
  row = row_loc;
  rot = rotation;
  color = base_color;
  return true;
}

void TCell::OnLoop() {
}

void TCell::OnRender() {
  glPushMatrix();
  glRotatef(rot, 0, 0, 1.0f);

  glColor3ub(color.red, color.green, color.blue);

  glBegin(GL_QUADS);
  glVertex2i(20 * column - 40, 20 * row - 40);
  glVertex2i(20 * column - 20, 20 * row - 40);
  glVertex2i(20 * column - 20, 20 * row - 20);
  glVertex2i(20 * column - 40, 20 * row - 20);
  glEnd();

  glPopMatrix();
}

void TCell::OnCleanup() {
}

void TCell::RotateRight() {
  rot += 90;
  rot %= 360;
}

void TCell::RotateLeft() {
  rot -= 90;
  rot %= 360;
}

void TCell::MoveLeft() {
  column--;
}

void TCell::MoveRight() {
  column++;
}

void TCell::MoveUp() {
  row--;
}

void TCell::MoveDown() {
  row++;
}
