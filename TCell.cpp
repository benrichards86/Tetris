#include <GL/glu.h>
#include <GL/gl.h>
#include "RGBColor.hpp"
#include "TCell.hpp"

using namespace tetris;

TCell::TCell() {
  x = y = 0;
  rot = 0;
  color.red = color.green = color.blue = 255;
}

TCell::~TCell() {
}

bool TCell::OnLoad(int x_loc, int y_loc, int rotation, RGBColor base_color) {
  x = x_loc;
  y = y_loc;
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
  glVertex2i(20 * x - 40, 20 * y - 40);
  glVertex2i(20 * x - 20, 20 * y - 40);
  glVertex2i(20 * x - 20, 20 * y - 20);
  glVertex2i(20 * x - 40, 20 * y - 20);
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
  x--;
}

void TCell::MoveRight() {
  x++;
}

void TCell::MoveUp() {
  y++;
}

void TCell::MoveDown() {
  y--;
}
