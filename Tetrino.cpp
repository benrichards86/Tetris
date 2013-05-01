#include <iostream>
#include "Tetrino.h"

#define CELL_SIZE 20

Tetrino::Tetrino() {
  x = y = 0;
  rotation = 0;
  type = -1;
}

Tetrino::~Tetrino() {
}

void Tetrino::SetLocation(int x_loc, int y_loc) {
  x = x_loc;
  y = y_loc;
}

void Tetrino::RotateRight() {
  rotation += 90;
  rotation %= 360;
}

void Tetrino::RotateLeft() {
  rotation -= 90;
  rotation %= 360;
}

void Tetrino::DrawCells(unsigned int cells) {
  glNewList(tetrino_drawlist, GL_COMPILE);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      if ((cells >> (j * 4 + i)) & 1) {
	glBegin(GL_QUADS);
	glVertex2i(-40 + 20 * i, -40 + 20 * j);
	glVertex2i(-20 + 20 * i, -40 + 20 * j);
	glVertex2i(-20 + 20 * i, -20 + 20 * j);
	glVertex2i(-40 + 20 * i, -20 + 20 * j);
	glEnd();
      }
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
bool Tetrino::OnLoad(int tetrino_type) {
  type = tetrino_type;
  tetrino_drawlist = glGenLists(1);
  switch(type) {
  case 0: {
    // . X . .
    // . X . .
    // . X X .
    // . . . .
    DrawCells(0x0622);
    break;
  }
  case 1: {
    // . X . .
    // . X . .
    // . X . .
    // . X . .
    DrawCells(0x2222);
    break;
  }
  case 2: {
    // . . X .
    // . . X .
    // . X X .
    // . . . .
    DrawCells(0x0644);
    break;
  }
  case 3: {
    // . . . .
    // . X . .
    // X X X .
    // . . . .
    DrawCells(0x0720);
    break;
  }
  case 4: {
    // . . . .
    // X X . .
    // . X X .
    // . . . .
    DrawCells(0x0630);
    break;
  }
  case 5: {
    // . . . .
    // . . X X
    // . X X .
    // . . . .
    DrawCells(0x0360);
    break;
  }
  case 6: {
    // . . . .
    // . X X .
    // . X X .
    // . . . .
    DrawCells(0x0660);
    break;
  }
  default: {
    std::cout << "Wrong type!" << std::endl;
    break;
  }
  }

  return true;
}

void Tetrino::OnLoop() {
}

void Tetrino::OnRender() {
  switch(type) {
  case 0: glColor3ub(100, 100, 255); break;
  case 1: glColor3ub(100, 255, 100); break;
  case 2: glColor3ub(100, 255, 255); break;
  case 3: glColor3ub(255, 100, 100); break;
  case 4: glColor3ub(255, 100, 255); break;
  case 5: glColor3ub(255, 255, 100); break;
  case 6: glColor3ub(255, 180, 100); break;
  default: glColor3ub(255, 255, 255); break;
  }
  glPushMatrix();
  glTranslated(x, y, 0);
  glRotatef(rotation, 0, 0, 1.0f);  
  glCallList(tetrino_drawlist);
  glPopMatrix();
}

void Tetrino::OnCleanup() {
}
