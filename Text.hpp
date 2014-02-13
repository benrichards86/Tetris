// Text.hpp
// Defines a text string that can be drawn at an (x, y, z) coordinate.

#ifndef TEXT_HPP
#define TEXT_HPP

#include <GL/glu.h>
#include <GL/gl.h>
#include <string>

namespace tetris {

class Text {
private:
  int x_coord;
  int y_coord;
  int z_coord;

public:
  Text();
  ~Text();

public:
  bool OnLoad();
  void OnLoop();
  void OnRender();
  void OnCleanup();

public:
  void SetText(std::string new_text);
  const char* GetText() {
    return text_str.c_str();
  }

private:
  std::string text_str;

};

}

#endif
