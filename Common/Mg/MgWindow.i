//-*-C++-*-
//
// MgWindow.i: swig interface for MgWindow
//

class MgWindow {
public:
  MgWindow();
  ~MgWindow();

  void SetCurrentPosition(int xMin, int xMax, int yMin, int yMax);

#  %addmethods {
#    void SetCurrentPosition(int xMin, int xMax, int yMin, int yMax) {
#      Position pos = {xMin, xMax, yMin, yMax};
#      SetCurrentPosition(pos);
#    }
#  }

};
