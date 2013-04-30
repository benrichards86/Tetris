#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

class Tetrino {
 public:
  int x;
  int y;
  GLfloat rotation;
  int type;
  GLuint tetrino_drawlist;

 public:
  Tetrino();
  virtual ~Tetrino();

 public:
  virtual bool OnLoad(int tetrino_type);
  virtual void SetLocation(int x_loc, int y_loc);
  virtual void SetRotation(GLfloat rot);
  virtual void OnLoop();
  virtual void OnRender();
  virtual void OnCleanup();
};

