//-*-C++-*-
#ifndef MGPROPERTY_H
#define MGPROPERTY_H


// class MgProperty
// 
// The MgProperty class is a parent to appearance-type classes such as lighting
// and material.  Generally, these classes are read and written the same
// way -- a list of options and values.  To make these load/save routines
// more consistent across the board, they should all be subclasses of this
// class.
//
// OOGL ASCII format:
//      <appearance-name> [ "{" ] options ... [ "}" ]
// Options may be of several types:
//      [*] [+/-] keyword
//      keyword args...
// No BINARY format is supported.
//
// To use this class (see MgAppearance for an example):
//
// (1) Make a subclass of MgProperty.
//
// (2) Create an array of KeywordTable entries:
//      word    - the keyword for this option
//      id      - any integer that lets you identify the keyword
//      mask    - what bit to set in mFlags
//     *numargs - the number of arguments that follow
//      typargs - the type of arguments that follow, either
//                      ARGS_NA, ARGS_INT, ARGS_REAL or ARGS_STRING
//
// *PROBLEM:  Because of the way that tokens are read, you can have no more
//  than one string for an argument.  See IoOldOoglToken to see why.
//
// *PROBLEM:  The arguments are stored in a static array of size MAX_AP_ARGS.
//  Thus, you can have no more than MAX_AP_ARGS arguments.
//
// (3) Override the following virtual functions:
//
//      const char *GetKeyword();
//              - Returns a keyword for this class (e.g. "appearance"
//                or "light").  Used for reading and writing.
//      const KeywordTable *GetKeywordTable();
//              - Returns the table you made in (2).
//      int GetNumKeywords();
//              - Returns the number of elements in that table.  This can
//                most easily be done by a line like this:
//                { return sizeof(tab)/sizeof(tab[0]); }
//      const char *GetIndent();
//              - Returns a string used to indent when writing this class.
//
//      int LoadProcess(IoOldOoglLexer *lex, int id, void *args);
//              - This is called after each option and the corresponding
//                args are read.  'id' contains the ID from the the table
//                you made.  'args' points to the arguments.  For ARGS_INT
//                and ARGS_REAL, this points to a list of int's and float's
//                respectively.  For ARGS_STRING, this points to the address
//                of a character pointer (a char**) that holds the token string.
//                Handle special options here.
//      int SaveProcess(IoDataStream *s, int mask);
//              - This is called after each option name is written.
//                Handle ALL options with arguments here.
//      int SaveProcessMore(IoDataStream *s);
//              - This is called after all options have been written out.
//                Handle options not already covered in this routine.
//
// While reading options, when an option is specified it's corresponding
// bit in the mValid field is set.  If a minus sign does NOT precede the
// option name, then the corresponding flag will be set in mFlags, too.
// If a minus sign DOES precede the option name, then the corresponding
// flag in mFlags will be cleared.

#include "RefObject.h"
#include "StorageObject.h"

#define MAX_AP_ARGS 10
enum KeywordArgType { ARGS_NA, ARGS_INT, ARGS_REAL, ARGS_STRING };

struct KeywordTable
{
    char *word;
    short id;
    unsigned short mask;
    short numargs;
    KeywordArgType typargs;
};

class MgProperty : virtual public RefObject , public StorageObject
{
    TYPE_DECLARE_TYPEINFO(MgProperty);
public:
    MgProperty();
    virtual ~MgProperty() { }

    int GetFlags()      { return mFlags; } 
    int GetValid()      { return mValid; }
    int GetOverride()   { return mOverride; }
                                  
    int GetValid(unsigned int valid)        { return(mValid & valid); }
    int GetOverride(unsigned int override)  { return(mOverride & override); }

    ////////////////////////////////////////////////////////////////////////
    // Added by John McDonald 5/27/97 -- The following are just simply    //
    // for setting Flags and Valids.  No validity checking is implemented //
    ////////////////////////////////////////////////////////////////////////
    void SetFlags(unsigned int flags)           { mFlags = flags; }
    void SetValid(unsigned int valid)           { mValid = valid; }
    void SetOverride(unsigned int override)     { mOverride = override; }

    void SetDo(int bitmask);
    void SetDont(int bitmask);

    // Reading:  Call Load(lex) to read this class.  Don't
    // redefine these function in the subclass.
    virtual int Load(const char *fname);                // Not used.
    virtual int Load(class IoDataStream *s) { return 0; }       // Not used.
  //    virtual int Load(class IoOldOoglLexer *lex);

    // Writing:  Call Save(s) to save this class.  If you want
    // to change the name of the class written out, use Save(s, "otherword");
    // Do not redefine these functions in the subclass.
    virtual int Save(class IoDataStream *s) { return(Save(s, GetKeyword())); }
    virtual int Save(class IoDataStream *s, const char *keyword);

    // DO redefine these in the subclass.  A return value of 1 means it was
    // successful.  See top of file for description of these functions.
    // These are called within Load and Save.
  //    virtual int LoadProcess(IoOldOoglLexer *lex, int id, void *args) { return 1; }
    virtual int SaveProcess(IoDataStream *s, int mask) { return 1; }
    virtual int SaveProcessMore(IoDataStream *s) { return 1; }

    // You won't be able to compile if you don't redefine these in the subclass.
    // No default values are supplied.  See top of file for description of
    // these functions.
    virtual const char *GetKeyword() = 0;
    virtual const KeywordTable *GetKeywordTable() = 0;
    virtual int GetNumKeywords() = 0;
    virtual const char *GetIndent() { return ""; }

    // Bitwise ORable values for mergeflags arguments
    typedef enum {
        F_NEW          = 0x0,  // create a new object as a result of the merge
        F_INPLACE      = 0x1,  // Merge in place
        F_OVEROVERRIDE = 0x2   // src replaces dst even without src override
    } MergeBits;

    // NOTE: the intended combinations of the above are:
    //   F_NEW
    //   F_INPLACE
    //   F_NEW | F_OVEROVERIDE
    //   F_INPLACE | F_OVEROVERIDE


    static int MergeMaskNew(const MgProperty *dst, const MgProperty *src)
    {
        return src
               ? src->mValid &~ (dst->mOverride &~ src->mOverride)
               : 0;
    }


    // The MgMaterial/MgLighting/MgAppearance Merge() functions use the
    // following function to generate the bitmask of properties to merge:
    static int MergeMask(MgProperty *dst, MgProperty *src, int mergeflags)
    {
        return src
            ? (mergeflags & MgProperty::F_OVEROVERRIDE)
            ? src->mValid
            : src->mValid &~ (dst->mOverride &~ src->mOverride)
            : 0;
    }
    //////////////////////////////////////////////////////////////////////
    // Explanation of the MergeMask (mbp Thu Dec 11 11:24:25 1997):
    // The above is equivalent to this:
    //     if (src == NULL) return 0;
    //     else {
    //         if (mergflags & MgProperty::F_OVEROVERRIDE) return src->mValid;
    //         else {
    //          return src->mValid & (~mOverride | src->mOverride);
    //         }
    //     }
    //
    // What this means is:
    //   1. if there is no src object, don't merge anything
    //   2. if F_OVEROVERRIDE is set in then mergeflags parameter,
    //      then merge in everything that's valid in the src object.
    //   3. Otherwise, proceed as follows:
    //        For starters, we only consider things in src that are valid.
    //        So we have
    // 
    //            mask = src->mValid & ...
    // 
    //        Of those things in src that are valid, we want to pick
    //        up the ones that "this" does NOT explicity override,
    //        plus any that src DOES explicitly override, i.e. we have
    // 
    //          mask = src->mValid & (~mOverride | src->mOverride);
    // 
    //        (This means that "src" wins out if both it and "this"
    //        want to override a particular field.)
    //////////////////////////////////////////////////////////////////////


protected:
    unsigned int  mFlags;
    unsigned int  mValid;    // These bits control inheritance of these fields
    unsigned int  mOverride; // Controls whether parent field overrides child

private:
    typedef union 
    { 
        float f; 
        int i; 
        char *s; 
    } AnyArg;

    static AnyArg spReadArgs[MAX_AP_ARGS];
};


#endif // MGPROPERTY_H
