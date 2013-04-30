#include <iostream>
#include "Tetrino.h"

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

void Tetrino::SetRotation(GLfloat rot) {
  rotation = rot;
}

// Tetrinos in a 80x80 pixel square, grid lines every 20px
bool Tetrino::OnLoad(int tetrino_type) {
  type = tetrino_type;
  tetrino_drawlist = glGenLists(1);
  switch(type) {
  case 0: {
    glNewList(tetrino_drawlist, GL_COMPILE);
    glBegin(GL_QUADS);

    glVertex2i(0, 20);
    glVertex2i(20, 20);
    glVertex2i(20, 60);
    glVertex2i(0, 60);

    glVertex2i(0, 60);
    glVertex2i(40, 60);
    glVertex2i(40, 80);
    glVertex2i(0, 80);

    glEnd();
    glEndList();
    break;
  }
  case 1: {
    glNewList(tetrino_drawlist, GL_COMPILE);
    glBegin(GL_QUADS);
    glVertex2i(20, 0);
    glVertex2i(40, 0);
    glVertex2i(40, 80);
    glVertex2i(20, 80);
    glEnd();
    glEndList();
    break;
  }
  case 2: {
    glNewList(tetrino_drawlist, GL_COMPILE);
    glBegin(GL_QUADS);

    glVertex2i(40, 20);
    glVertex2i(60, 20);
    glVertex2i(60, 60);
    glVertex2i(40, 60);

    glVertex2i(20, 60);
    glVertex2i(60, 60);
    glVertex2i(60, 80);
    glVertex2i(20, 80);

    glEnd();
    glEndList();
    break;
  }
  case 3: {
    glNewList(tetrino_drawlist, GL_COMPILE);
    glBegin(GL_QUADS);

    glVertex2i(0, 60);
    glVertex2i(60, 60);
    glVertex2i(60, 80);
    glVertex2i(0, 80);

    glVertex2i(20, 40);
    glVertex2i(40, 40);
    glVertex2i(40, 60);
    glVertex2i(20, 60);

    glEnd();
    glEndList();
    break;
  }
  case 4: {
    glNewList(tetrino_drawlist, GL_COMPILE);
    glBegin(GL_QUADS);

    glVertex2i(0, 40);
    glVertex2i(40, 40);
    glVertex2i(40, 60);
    glVertex2i(0, 60);

    glVertex2i(20, 60);
    glVertex2i(60, 60);
    glVertex2i(60, 80);
    glVertex2i(20, 80);

    glEnd();
    glEndList();
    break;
  }
  case 5: {
    glNewList(tetrino_drawlist, GL_COMPILE);
    glBegin(GL_QUADS);

    glVertex2i(20, 40);
    glVertex2i(60, 40);
    glVertex2i(60, 60);
    glVertex2i(20, 60);

    glVertex2i(0, 60);
    glVertex2i(40, 60);
    glVertex2i(40, 80);
    glVertex2i(0, 80);

    glEnd();
    glEndList();
    break;
  }
  case 6: {
    glNewList(tetrino_drawlist, GL_COMPILE);
    glBegin(GL_QUADS);

    glVertex2i(0, 40);
    glVertex2i(40, 40);
    glVertex2i(40, 80);
    glVertex2i(0, 80);

    glEnd();
    glEndList();
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
