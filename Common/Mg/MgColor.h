//-*-C++-*-
#ifndef MGCOLOR_H
#define MGCOLOR_H

///////////////////////////////////////////////////////////////////////
// Added by John McDonald -- 6/4/97 -- Made both of these derive     //
// from a common base class for the color change dialog box.         //
///////////////////////////////////////////////////////////////////////

class MgRGB 
{
public: 
    virtual ~MgRGB() { }

    virtual void   SetRed(double r) {};
    virtual void   SetGreen(double g) {};
    virtual void   SetBlue(double b) {};
    virtual double GetRed() { return(0.0); };
    virtual double GetGreen() { return(0.0); };
    virtual double GetBlue() { return(0.0); };
};

class MgColor : public MgRGB {
protected:
    float mR,mG,mB;
public:
    MgColor() {
        mR = mG = mB = 1.0f;
    }
    MgColor(double r, double g, double b) {
        mR = (float)r; 
        mG = (float)g;
        mB = (float)b ;
    }
    void SetRGB(double r, double g, double b) {
        mR = (float)r; 
        mG = (float)g;
        mB = (float)b ;
    }

    ////////////////////////////////////////////////////////////////////////
    // Added by John McDonald 6/4/97 -- I added these equality operators  //
    // to fix a problem with having a base class and casting arrays       //
    // to MgColor.   The problem is that the first element in an MgColor  //
    // is now a virtual table pointer.  This should fix the problem.      //
    // just say "color = f" where f is a pointer to a float.  Be careful  //
    // that f points to an array of the appropriate size, but this was    //
    // also a problem with the earlier notation "color = *(MgColor  *)f"  //
    ////////////////////////////////////////////////////////////////////////

    void operator=(double *d) { mR = (float)d[0]; mG = (float)d[1]; mB = (float)d[2]; }
    void operator=(float *d) { mR = d[0]; mG = d[1]; mB = d[2]; }
    void SetRed(double r)   { mR = (float)r; }
    void SetGreen(double g) { mG = (float)g; }
    void SetBlue(double b)  { mB = (float)b; }
    double GetRed()   { return mR; }
    double GetGreen() { return mG; }
    double GetBlue()  { return mB; }

    double Normalize();

    // "Cast to float *" operator.  Returns a pointer to an
    // array of 3 floats representing the RGB values of this color.
    operator float * () {
        return (float*)(&mR);
    }
};

class MgColorA : public MgRGB {
protected:
    float mR,mG,mB,mA;
public:
    MgColorA() {
        mR = mG = mB = mA = 1.0f;
    }
    MgColorA(double r, double g, double b, double a) {
        mR = (float)r; 
        mG = (float)g;
        mB = (float)b ;
        mA = (float)a ;
    }
    void SetRGBA(double r, double g, double b, double a) {
        mR = (float)r; 
        mG = (float)g;
        mB = (float)b ;
        mA = (float)a ;
    }

    ////////////////////////////////////////////////////////////////////////
    // Added by John McDonald 6/4/97 -- I added these equality operators  //
    // to fix a problem with having a base class and casting arrays       //
    // to MgColorA.  The problem is that the first element in an MgColorA //
    // is now a virtual table pointer.  This should fix the problem.      //
    // just say "color = f" where f is a pointer to a float.  Be careful  //
    // that f points to an array of the appropriate size, but this was    //
    // also a problem with the earlier notation "color = *(MgColorA *)f"  //
    ////////////////////////////////////////////////////////////////////////

    void operator=(double *d) { mR = (float)d[0]; mG = (float)d[1]; mB = (float)d[2]; mA = (float)d[3]; }
    void operator=(float *d) { mR = d[0]; mG = d[1]; mB = d[2]; mA = d[3]; }

    void   SetRed(double r)   { mR = (float)r; }
    void   SetGreen(double g) { mG = (float)g; }
    void   SetBlue(double b)  { mB = (float)b; }
    void   SetAlpha(double a)  { mA = (float)a; }
    double GetRed()   { return mR; }
    double GetGreen() { return mG; }
    double GetBlue()  { return mB; }
    double GetAlpha()  { return mA; }

    // "Cast to float *" operator.  Returns a pointer to an
    // array of 4 floats representing the RGB values of this color.
    operator float * () {
        return (float*)(&mR);
    }
};


#endif // MGCOLOR_H
