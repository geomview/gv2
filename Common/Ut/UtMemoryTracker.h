//-*-C++-*-

// class UtMemoryTracker
//     prerequisites:
//         compile: UtLList.h
//	      link: UtString.o
//
// This class is for debugging purposes only.  Its purpose is
// to help keep track of memory allocations when trying to find
// problems.

#include "UtLList.h"

#include <stdio.h>


class UtMemoryTrackerNode {
public:
    UtMemoryTrackerNode(){}
    UtMemoryTrackerNode(void *p, int location, char *type);
    ~UtMemoryTrackerNode();

    void *mpPointer;
    int   mLocation;
    char *mpType;
};

class UtMemoryTracker {
public:
    static void New(void *p, int location, char *type);
    static void Delete(void *p, int location);
    static void ReportAll(char *type = NULL);
private:
    static FILE *spFp;
    static void OpenFile();
    static void CloseFile();
    static void FlushFile();
    static UtLList<UtMemoryTrackerNode> sList;
};
