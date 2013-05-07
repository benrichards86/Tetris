#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <vector>
#include "Tetrino.hpp"
#include "TCell.hpp"

using namespace tetris;

Tetrino::Tetrino() {
  row = 0;
  column = 10;
  rotation = 0;
  cell_mask = 0xffff;
}

Tetrino::~Tetrino() {
  for (int i = 0; i < vec_rep.size(); i++)
    delete vec_rep[i];
}

void Tetrino::RotateRight() {
  rotation += 90;
  rotation %= 360;

  for (int i = 0; i < vec_rep.size(); i++)
    vec_rep[i]->RotateRight();
}

void Tetrino::RotateLeft() {
  rotation -= 90;
  rotation %= 360;

  for (int i = 0; i < vec_rep.size(); i++)
    vec_rep[i]->RotateLeft();
}

bool Tetrino::LoadCells(unsigned int cells, RGBColor color_value) {
  cell_mask = cells;
  color = color_value;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((cells >> (j * 4 + i)) & 1) {
	TCell *t = new TCell();
	if (t->OnLoad(i, j, rotation, color))
	  vec_rep.push_back(t);
      }
    }
  }

  return vec_rep.size() > 0;
}

// Tetrinos in a 80x80 pixel square, grid lines every 20px
bool Tetrino::OnLoad(int type) {
  RGBColor color;
  switch(type) {
  case 0: {
    color.red = color.green = 100;
    color.blue = 255;
    cell_mask = 0x0622;
    break;
  }
  case 1: {
    color.red = color.blue = 100;
    color.green = 255;
    cell_mask = 0x2222;
    break;
  }
  case 2: {
    color.red = 100;
    color.green = color.blue = 255;
    cell_mask = 0x0644;
    break;
  }
  case 3: {
    color.red = 255;
    color.green = color.blue = 100;
    cell_mask = 0x0720;
    break;
  }
  case 4: {
    color.red = color.blue = 255;
    color.green = 100;
    cell_mask = 0x0630;
    break;
  }
  case 5: {
    color.red = color.green = 255;
    color.blue = 100;
    cell_mask = 0x0360;
    break;
  }
  case 6: {
    color.red = 255;
    color.green = 180;
    color.blue = 100;
    cell_mask = 0x0660;
    break;
  }
  default: {
    color.red = color.green = color.blue = 255;
    cell_mask = 0xa5a5;
    break;
  }
  }

  return LoadCells(cell_mask, color);
}

void Tetrino::OnLoop() {
}

void Tetrino::OnRender() {
  for (int i = 0; i < vec_rep.size(); i++) {
    glPushMatrix();
    glTranslated(column * 20, row * 20, 0);
    vec_rep[i]->OnRender();
    glPopMatrix();
  }
  
#ifdef DEBUG
  glPushMatrix();
  glTranslated(column * 20, row * 20, 0);
  glColor3ub(255, 255, 255);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      glBegin(GL_LINE_LOOP);
      glVertex2i(20 * (i - 1), 20 * (j - 1));
      glVertex2i(20 * (i - 2), 20 * (j - 1));
      glVertex2i(20 * (i - 2), 20 * (j - 2));
      glVertex2i(20 * (i - 1), 20 * (j - 2));  
      glEnd();
    }
  }

  glColor3f(1, 0, 0);
  glPointSize(4);
  glBegin(GL_POINTS);
  glVertex2i(0, 0);
  glEnd();
  glPopMatrix();
#endif
}
  
void Tetrino::OnCleanup() {
}

void Tetrino::MoveLeft() {
  column--;
  for (int i = 0; i < vec_rep.size(); i++)
    vec_rep[i]->MoveLeft();
}

void Tetrino::MoveRight() {
  column++;
  for (int i = 0; i < vec_rep.size(); i++)
    vec_rep[i]->MoveRight();
}

void Tetrino::MoveUp() {
  row--;
  for (int i = 0; i < vec_rep.size(); i++)
    vec_rep[i]->MoveUp();
}

void Tetrino::MoveDown() {
  row++;
  for (int i = 0; i < vec_rep.size(); i++)
    vec_rep[i]->MoveDown();
}

TCell* Tetrino::operator[](int index) {
  return vec_rep[index];
}
