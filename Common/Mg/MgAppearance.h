//-*-C++-*-
#ifndef MGAPPEARANCE_H
#define MGAPPEARANCE_H


// class MgAppearance
// 
// Geometric objects can have associated "appearance" information,
// specifying shading, lighting, color, wireframe vs. shaded-surface
// display, and so on.  Appearances are inherited through object hierarchies,
// e.g. attaching an appearance to a LIST means that the appearance is
// applied to all the LIST's members. 
//
// Some appearance-related properties are relegated to "material" and
// "lighting" substructures. Take care to note which properties belong to
// which structure. 

#include "MgProperty.h"

class MgAppearance : public MgProperty
{
public:
    MgAppearance() { Init(); }
    ~MgAppearance();

    // MgAppearance(const MgAppearance &src);
    // MgAppearance & operator= (MgAppearance &src);
    // NO COPY CONSTRUCTOR or operator=!
    // MgAppearance does not have, and should not be given, a copy
    // constructor or an overloaded assignment operator.  This is
    // because it would be too confusing to try to remember what it
    // does with the pointers an MgAppearance contains.  There are
    // situations where one wants to do a deep copy, other situations
    // where one wants a shallow copy, and other situations where one
    // wants something in between.  It's best to leave these operations
    // to member functions with very explicit names that clarify what
    // they do.

    enum
    {
        F_FACEDRAW      = 0x0001,       // Draw faces
        F_EDGEDRAW      = 0x0002,       // Draw edges
        F_TRANSPARENCY  = 0x0004,       // Enable transparency
        F_EVERT         = 0x0008,       // Evert surface normals
        F_NORMALDRAW    = 0x0010,       // Draw surface normals
        F_VECTDRAW      = 0x0020,       // Draw vectors/points
        F_KEEPCOLOR     = 0x0040,       // Not susceptible to N-D coloring
        F_BACKCULL      = 0x0080,       // Enable back-face culling
        F_SHADELINES    = 0x0100,       // Enable line (edge & vect)
        //  lighting&shading
        F_CONCAVE       = 0x0200,       // Expect concave polygons
        F_SHADING       = 0x0400,       // Use 'shading' value
        F_NORMALSCALE   = 0x0800,       // Use 'nscale' value to draw normals
        F_LINEWIDTH     = 0x1000,       // Use 'linewidth' value
        F_PATCHDICE     = 0x2000,       // Dicing (use udice, vdice fields)
    };


    // Possible values for ap->shading field; these MUST be consecutive !!
    // (code outside the appearance library depends on this fact)
    typedef enum
    {
        F_CONSTANT      = 0,            // constant-colored (unlighted) faces
        F_FLAT          = 1,            // Flat-shaded, lighted faces
        F_SMOOTH        = 2,            // Gouraud-shaded faces, w/ lighting
        F_CSMOOTH       = 3,            // Gouraud-shaded faces, w/o lighting
    } ShadingType;

    ///////////////////////////////////////////////////////////////////////
    // Added by John McDonald 5/20/97 -- The following functions
    // should have declared return types.  C++ will still assume that
    // they are ints, but VC++ 5.0 seems to want to interpret them as
    // constructors.  Of course, it can't do this since they have the
    // wrong names.  Therefore, it just gives a warning (instead of an
    // error) and probably does the correct thing.  It is just a
    // general rule, though, that C++ likes to have pretty much
    // everything (with regards to type) spelled out explicitly.  The
    // warning given follows:
    // -------------------------------------------------------------------
    // warning C4183: 'HasSmoothShading': member function definition looks
    // like a ctor, but name does not match enclosing class
    //////////////////////////////////////////////////////////////////////
    int HasSmoothShading() { return mShading >= F_SMOOTH; }
    int HasShading()
    {
        // Egads. I think this is just a very contorted way of testing
        // whether shading is either F_FLAT or F_SMOOTH.  I.e. I think
        // it's eqivalent to "return ((shading==F_FLAT) ||
        // (shading==F_SMOOTH))" Ask Stuart about this. Presumably we're
        // doing it this way for efficiency, but do two equality tests and
        // a logical OR really take that much time?
        // mbp Tue May 06 09:49:14 1997
        //
        // It may be that the return value of this function is expected
        // to be a mask rather than a boolean.
        // lori Tue Sep 23 17:00:09 CDT 1997
        //
        return ((1<<(mShading)) & ((1<<F_FLAT)|(1<<F_SMOOTH)));
    }

    void Default();

    void SetFrontMaterial(class MgMaterial *mat);
    void SetBackMaterial(class MgMaterial *mat);
    void SetLighting(class MgLighting *lighting);

    void SetNormalScale(double nscale);
    void SetLineWidth(int linewidth);
    void SetShading(ShadingType shading);
    void SetPatchDice(int u, int v);

    class MgMaterial * GetFrontMaterial()      { return mpMat; }
    class MgMaterial * GetBackMaterial()       { return mpBackMat; }
    class MgLighting * GetLighting()           { return mpLighting; }
    double             GetNormalScale()        { return mNormalScale; }
    int                GetLineWidth()          { return mLineWidth; }
    ShadingType        GetShading()            { return mShading; }
    void               GetPatchDice(int *u, int *v)
                           { *u = mDice[0]; *v = mDice[1]; }
    MgAppearance *MergeNew(const MgAppearance *src);

    void          Copy(MgAppearance *from);
    void          CopyShared(MgAppearance *src);

  //    virtual int LoadProcess(IoOldOoglLexer *lex, int id, void *args);
    virtual int SaveProcess(IoDataStream *s, int mask);
    virtual int SaveProcessMore(IoDataStream *s);

    virtual const char *         GetKeyword();
    virtual const KeywordTable * GetKeywordTable();
    virtual int                  GetNumKeywords();

private:
    void Init();
    void CopyShallow(MgAppearance *src);

private:
    class MgMaterial    * mpMat;          // material properties for front faces
    class MgMaterial    * mpBackMat;      // material properties for back faces
    class MgLighting    * mpLighting;     // attached lighting
    class MgTexture     * mpTexture;      // texture
    float                 mNormalScale;  // scale factor for drawing normals
    int                   mLineWidth;    // how wide do lines appear (pixels) ?
    ShadingType           mShading;      // F_{CONSTANT,FLAT,SMOOTH}
    short                 mDice[2];      // u, v patch dicing parameters
};


#endif // MGAPPEARANCE_H
