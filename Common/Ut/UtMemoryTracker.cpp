#include "UtMemoryTracker.h"
#include "UtString.h"

UtLList<UtMemoryTrackerNode> UtMemoryTracker::sList;
FILE *UtMemoryTracker::spFp = NULL;

UtMemoryTrackerNode::UtMemoryTrackerNode(void *p, int location, char *type)
{
    mpPointer = p;
    mLocation = location;
    mpType = type;
}

UtMemoryTrackerNode::~UtMemoryTrackerNode(){}


void UtMemoryTracker::OpenFile()
{
    if (!spFp) {
        spFp = fopen("memory.log", "w");
    }
}

void UtMemoryTracker::CloseFile()
{
    if (spFp) fclose(spFp);
    spFp = NULL;
}

void UtMemoryTracker::FlushFile()
{
    if (spFp) fflush(spFp);
}

void UtMemoryTracker::New(void *p, int location, char *type)
{
    OpenFile();
    UtMemoryTrackerNode mt(p, location, type);
    sList.AppendItem(mt);
    fprintf(spFp,
           "UtMemoryTracker: new %s allocated; address=%8x, location=%3d\n",
           type, p, location);
    FlushFile();
}

void UtMemoryTracker::Delete(void *p, int location)
{
    OpenFile();
    for (UtLListIter<UtMemoryTrackerNode> it(sList);
         it;
         ++it)
    {
        UtMemoryTrackerNode *pMt = it();
        if (pMt->mpPointer == p)
        {
            fprintf(spFp,
                   "UtMemoryTracker: Deleting %s, address=%8x; delete location=%3d\n",
                   pMt->mpType, pMt->mpPointer, location);
            sList.RemoveItemByPointer(pMt);
            break;
        }
    }
    FlushFile();
}

void UtMemoryTracker::ReportAll(char *type)
{
    OpenFile();
    fprintf(spFp, "UtMemoryTracker list of ");
    if (type == NULL) fprintf(spFp, "all pointers on record:\n");
    else fprintf(spFp, "\"%s\" pointers on record:\n", type);
    for (UtLListIter<UtMemoryTrackerNode> it(sList);
         it;
         ++it)
    {
        UtMemoryTrackerNode *pMt = it();
        if (type == NULL)
        {
            fprintf(spFp,
                   "    %s: address=%8x; alloc location=%3d\n",
                   pMt->mpType, pMt->mpPointer, pMt->mLocation);
        }
        else
        {
            if (UtString::Streq(pMt->mpType, type))
            {
                fprintf(spFp,
                        "    address=%8x; delete location=%3d\n",
                        pMt->mpPointer, pMt->mLocation);
            }
        }
    }
    FlushFile();
}
    
