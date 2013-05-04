#include <iostream>
#include "Tetrino.hpp"

Tetrino::Tetrino() {
  x = y = 0;
  rotation = 0;
  cells = 0xffff;
  array_rep = new int[4][4];
}

Tetrino::~Tetrino() {
  delete array_rep;
}

void Tetrino::SetLocation(int x_loc, int y_loc) {
  x = x_loc;
  y = y_loc;
}

void Tetrino::RotateRight() {
  rotation += 90;
  rotation %= 360;
  int (*new_rep)[4] = new int[4][4];
  
  // rotate
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      new_rep[j][i] = array_rep[i][3-j];

  delete array_rep;
  array_rep = new_rep;

#ifdef DEBUG
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      std::cout << array_rep[j][i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
#endif
}

void Tetrino::RotateLeft() {
  rotation -= 90;
  rotation %= 360;
  int (*new_rep)[4] = new int[4][4];

  // rotate
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      new_rep[j][i] = array_rep[3-i][j];

  delete array_rep;
  array_rep = new_rep;

#ifdef DEBUG
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      std::cout << array_rep[j][i] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
#endif
}

int** Tetrino::ToArray() {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      array_rep[i][j] = ((cells >> (j * 4 + i)) & 1) ? 1 : 0;
  return reinterpret_cast<int**>(array_rep);
}

void Tetrino::DrawCells(unsigned int cells, RGBColor color) {
  glNewList(tetrino_drawlist, GL_COMPILE);
  glColor3ub(color.red, color.green, color.blue);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if ((cells >> (j * 4 + i)) & 1) {
	glBegin(GL_QUADS);
	glVertex2i(-40 + 20 * i, -40 + 20 * j);
	glVertex2i(-20 + 20 * i, -40 + 20 * j);
	glVertex2i(-20 + 20 * i, -20 + 20 * j);
	glVertex2i(-40 + 20 * i, -20 + 20 * j);
	glEnd();
	array_rep[i][j] = 1;
      }
      else
	array_rep[i][j] = 0;

#ifdef DEBUG
      glBegin(GL_LINE_LOOP);
      glVertex2i(-40 + 20 * i, -40 + 20 * j);
      glVertex2i(-20 + 20 * i, -40 + 20 * j);
      glVertex2i(-20 + 20 * i, -20 + 20 * j);
      glVertex2i(-40 + 20 * i, -20 + 20 * j);  
      glEnd();
#endif
    }
#ifdef DEBUG
  glColor3f(1, 0, 0);
  glPointSize(4);
  glBegin(GL_POINTS);
  glVertex2i(0, 0);
  glEnd();
#endif
  glEndList();
}

// Tetrinos in a 80x80 pixel square, grid lines every 20px
bool Tetrino::OnLoad(int type) {
  RGBColor color;
  tetrino_drawlist = glGenLists(1);
  switch(type) {
  case 0: {
    color.red = color.green = 100;
    color.blue = 255;
    cells = 0x0622;
    break;
  }
  case 1: {
    color.red = color.blue = 100;
    color.green = 255;
    cells = 0x2222;
    break;
  }
  case 2: {
    color.red = 100;
    color.green = color.blue = 255;
    cells = 0x0644;
    break;
  }
  case 3: {
    color.red = 255;
    color.green = color.blue = 100;
    cells = 0x0720;
    break;
  }
  case 4: {
    color.red = color.blue = 255;
    color.green = 100;
    cells = 0x0630;
    break;
  }
  case 5: {
    color.red = color.green = 255;
    color.blue = 100;
    cells = 0x0360;
    break;
  }
  case 6: {
    color.red = 255;
    color.green = 180;
    color.blue = 100;
    cells = 0x0660;
    break;
  }
  default: {
    color.red = color.green = color.blue = 255;
    cells = 0xa5a5;
    break;
  }
  }

  DrawCells(cells, color);

  return true;
}

void Tetrino::OnLoop() {
}

void Tetrino::OnRender() {
  glPushMatrix();
  glTranslated(x, y, 0);
  glRotatef(rotation, 0, 0, 1.0f);  
  glCallList(tetrino_drawlist);
  glPopMatrix();
}

void Tetrino::OnCleanup() {
}
