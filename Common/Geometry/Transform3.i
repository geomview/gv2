//-*-C++-*-
//
// Transform3.i: swig interface for Transform3
//

class Transform3 {
public:
  Transform3();
  ~Transform3();

  void Identity();
  void CRotateX(float angle);
  void CRotateY(float angle);
  void Translate(float x, float y, float z);
  void Scale(float x, float y, float z);

  char *ToString(char *buffer);
  char *ToLeakyString();
};
