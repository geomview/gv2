//-*-C++-*-
//
// MgWindow.i: swig interface for MgWindow
//

class MgWindow {
public:
  MgWindow();
  ~MgWindow();

  void SetCurrentPosition(int  xMin, int  xMax, int  yMin, int  yMax);
  int  GetCurrentPosition(int *xMin, int *xMax, int *yMin, int *yMax);

  int MapToStandardSquare(int x, int y,
			  double *OutValue, double *OutValue);

  %addmethods {
    int getXMin() { 
      MgWindow::Position pos;
      self->GetCurrentPosition(&pos);
      return pos.p_XMin;
    }
    int getXMax() { 
      MgWindow::Position pos;
      self->GetCurrentPosition(&pos);
      return pos.p_XMax;
    }
    int getYMin() { 
      MgWindow::Position pos;
      self->GetCurrentPosition(&pos);
      return pos.p_YMin;
    }
    int getYMax() { 
      MgWindow::Position pos;
      self->GetCurrentPosition(&pos);
      return pos.p_YMax;
    }


  }


#  %addmethods MgWindow {
#    void SetCurrentPosition(int xMin, int xMax, int yMin, int yMax) {
#      Position pos = {xMin, xMax, yMin, yMax};
#      SetCurrentPosition(pos);
#    }
#  }

};
