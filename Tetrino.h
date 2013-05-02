#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

class Tetrino {
 private:
  int x;
  int y;
  int rotation;
  int cells;
  GLuint tetrino_drawlist;
  int (*array_rep)[4];

  struct RGBColor {
    int red;
    int green;
    int blue;
  };

 public:
  Tetrino();
  ~Tetrino();

 public:
  bool OnLoad(int type);
  void OnLoop();
  void OnRender();
  void OnCleanup();

 public:
  void SetLocation(int x_loc, int y_loc);
  void RotateRight();
  void RotateLeft();
  int** ToArray();  

 private:
  void DrawCells(unsigned int cells, RGBColor color);

};

