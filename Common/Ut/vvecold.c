#include "ooglutil.h"

/*
 * Variable-sized arrays ("vectors").
 */

void
vvinit(vvec *v, int elsize, int minelems)
{
    v->elsize = elsize;
    v->count = 0;
    v->malloced = 0;
    v->dozero = 0;
    v->allocated = -minelems;
    v->base = NULL;
}

void
vvuse(vvec *v, void *buf, int allocated)
{
    vvfree(v);
    v->base = buf;
    v->allocated = allocated;
}

void
vvzero(vvec *v)
{
    v->dozero = 1;
    if(v->allocated > v->count)
	memset(v->base + v->elsize*v->count, 0,
		v->elsize * (v->allocated - v->count));
}

/*
 * Trim vvec to minimum size; ensure its buffer is malloced if it wasn't.
 */
void
vvtrim(vvec *v)
{
    int newalloc = (v->count > 0 ? v->count : 1);
    int want = newalloc * v->elsize;
    static char why[] = "trimming vvec";

    if(!v->malloced) {
	void *base = OOGLNewNE(char, want, why);
	if(v->base) memcpy(base, v->base, want);
	else memset(base, '\0', want);
	v->base = base;
	v->malloced = 1;
    } else if(v->allocated > v->count) {
	v->base = (void *)OOGLRenewNE(char, v->base, want, why);
    } else
	return;
    v->allocated = newalloc;
}

void
vvfree(vvec *v)
{
    if(v->malloced) {
	OOGLFree(v->base);
	v->base = NULL;
	v->malloced = 0;
    }
}

void
vvneeds(register vvec *v, int needed)
{
    if(needed > v->allocated) {
	int had = v->allocated;
	int want = needed + (needed>>2) + 1;

	if(had < 0) {
	    if(want < -had)
		want = -had;
	    had = 0;
	} else {
	    int next = had + (had>>1) + 2;
	    if(next > needed)
		want = next;
	}

	if(v->malloced) {
	    v->base = OOGLRenewNE(char, v->base,
			want * v->elsize, "extending vvec");
	    if(had > v->count) had = v->count;
	} else {
	    void *was = v->base;
	    v->base = OOGLNewNE(char, want * v->elsize, "allocating vvec");
	    if(v->count > 0 && had > 0)
		memcpy(v->base, was, (v->count<had ? v->count:had) * v->elsize);
	}
	v->allocated = want;
	v->malloced = 1;
	if(v->dozero)
	    memset(v->base + v->elsize * had, 0,
		v->elsize * (want-had));
    }
}

void *
vvindex(vvec *v, int index)
{
    if(index < 0) {
#if CUTOUT
XX 	OOGLError(1, "negative array index: %d", index);
#endif /* CUTOUT */
	return v->base;
    }
    if(index >= v->allocated)
	vvneeds(v, index+1);
    if(index >= v->count)
	v->count = index+1;
    return v->base + index*v->elsize;
}

void
vvcopy(vvec *src, vvec *dest) 
{
  char *newbase;
  if(src->base == NULL) {
    *dest = *src;
  } else {
    vvneeds(dest, src->allocated);
    newbase = dest->base;
    *dest = *src;
    dest->base = newbase;
    memcpy(dest->base, src->base, dest->allocated * dest->elsize);
  }
}
