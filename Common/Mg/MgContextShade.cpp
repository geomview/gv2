#include "MgContext.h"
#include <math.h>

#if 0

#define DOT(a,b)  ((a).x*(b).x + (a).y*(b).y + (a).z*(b).z)

#define CCMUL(A,B,C)  ((C).r=(A).r*(B).r, (C).g=(A).g*(B).g, (C).b=(A).b*(B).b)
#define CCADD(A,B,C)  ((C).r=(A).r+(B).r, (C).g=(A).g+(B).g, (C).b=(A).b+(B).b)

#define CSCALE(s, A, B) ( (B).r = (A).r * s, (B).g = (A).g * s, (B).b = (A).b * s, (B).a = (A).b * s)


#define CCSADD(A,B,s,C) \
         ((C).r += (s)*(A).r*(B).r, \
          (C).g += (s)*(A).g*(B).g, \
          (C).b += (s)*(A).b*(B).b)

//++MgContext::EucShade [nh`fvdtibef,mgshade.c]
/*
 * Euclidean shader
 *
 * We depend on the following mg features:
 *      mXStk.Top()->p_mHasInv (cleared whenever transform changes)
 *      mW2C, mC2W (initialized from camera at mgworldBegin())
 */
int MgContext::EucShade(int nv, HPoint3 *v, Point3 *n, MgColorA *c, MgColorA *cs)
{
    TransformStackNode  *mx = mXStk.Top();
    AppearanceStackNode *ma = mAStk.Top();
    struct MgLight *l;
    int i;
    HPoint3 V;
    Point3 N, I;
    float s;
    MgColor Ca, Ci;

    mEuck1 = ma->p_mLighting.attenmult;
    mEuck2 = ma->p_mLighting.attenmult2;
    mFog = ma->p_mLighting.attenconst;
#define EYE     ((HPoint3 *) (mC2W.D.M[3]))/* Eye (camera) position as an HPoint3 */

    if(!mx->p_mHasInv) {
      mx->p_mTinv.InverseOf(&mx->p_mT);
      mx->p_mHasInv = 1;
    }

    /* "ambient" color */
    
    Ca.SetRGB(0.0, 0.0, 0.0);
    CCSADD(ma->p_mMat.ambient, ma->p_mLighting.ambient, ma->p_mMat.ka, Ca);

    for(i = 0; i < nv; i++, v++, n++, c++, cs++) {
        MgColorA *thiscolor = c;
        float num;

                                        /* Transform point by T */
        mx->p_mT.HPoint3Transform(v, &V);  /* V = v in world coords */
        HPoint3::SubtractToPoint3(EYE, &V, &I);/* I=EYE-V (point-to-eye vector) */

        /* Is this vertex behind our eye?  If so, let's not shade it.
         * Speed up Shape of Space rendering.  This code may be questionable:
         * what if this is a vertex of a smooth-shaded polygon that extends
         * in front of our eye, too?
         */
        if(DOT(I, *((HPoint3 *)mC2W.D.M[2])) < 0) {
            /* Dummy -- just Ci = Cs. */
            *cs = *c;
            continue;
        }

        I.Unitize();

                                        /* Transform normal by T'^-1 */
        MgContext::Cotransform(mx->p_mTinv, n, &N);
                                        /* check if normal has 0 length! */
        num = sqrt(DOT(N,N));
        if (num == 0.0)
          num = 1;
        s = 1/num;

        if(DOT(N,I) < 0) {
            s = -s;                     /* Flip normal to face the viewer */

                /* Hack: use otherwise-useless emission color, if defined,
                 * as the back-side material color.
                 */
            if(ma->p_mMat.valid & MTF_EMISSION) {
                thiscolor = (MgColorA*)&ma->p_mMat.emission;
                thiscolor->a = 1.0;  // because emission is only a Color 
            }
        }

        N.x *= s;  N.y *= s;  N.z *= s;
        
                                        /* Ambient term */
        Ci = Ca;

        for(l = ma->p_mLighting.lights; l != NULL; l = l->next) {
            register Point3 *L;
            Point3 Lt;
            float bright, ls, ll, ln, power;

                                        /* Diffuse term */
            bright = l->intensity;
            if(l->globalposition.w == 0) {
                L = (Point3 *)&l->globalposition;
                ll = DOT(*L,*L);
            } else {
              HPoint3::SubtractToPoint3(&l->globalposition, &V, &Lt);
                L = &Lt;
                ll = DOT(Lt,Lt);
                /* ll = (ll > mEuck2) ? ll : mEuck2; */
                if (ll > 0.0)
                        power = pow((double)ll, (double)(-mEuck1/2.0));
                else
                  power = 1.0;
                        /* Inverse square falloff */
                bright *= power;
            }

            ln = DOT(*L,N);
            if(ln <= 0)                 /* Ignore lights shining from behind */
                continue;
            if (ll > 0.0)
              ls = sqrt(ll);
            else
              ls = 1.0;

            if (ls == 0.0) ls = 1.0;

            s = ma->p_mMat.kd * bright * (ln/ls);
                                        /* cosine law: L.N diffuse shading */

            CCSADD(l->color, *thiscolor, s, Ci);

            if(ma->p_mMat.ks > 0) {     /* Specular term */
                Point3 H;               /* H: halfway between L and I */
                float num;

                H.x = L->x/ls + I.x, H.y = L->y/ls + I.y, H.z = L->z/ls + I.z;
                num = DOT(H,H);
                if (num <= 0.0)
                  num = 1.0;
                else
                  num = sqrt(num);

                s = DOT(H,N) / num;
                                        /* cos angle(H,N) */

                        /* Note we need s>=0 for specular term to make sense.
                         * This should be true since we checked
                         * that both L.N and I.N are positive above.
                         */

                                        /* shininess = specular exponent */
                if (s > 0.0)
                  s = ma->p_mMat.ks * bright * pow(s, ma->p_mMat.shininess);
                else
                  s = ma->p_mMat.ks * bright;

                CCSADD(l->color, ma->p_mMat.specular, s, Ci);
            }
        }
        /* insert mFog code */
        if (mFog)        {
            float k1, k2;
            float d = V.Distance(EYE);
            MgColorA surfcolor, fogcolor;
            d = d - mEuck2;              /* mFog-free sphere of radius mEuck2 */
            if (d < 0) d = 0;
            k1 = exp( -mFog * d);
            k2 = 1.0 - k1;
            CSCALE(k1, Ci, surfcolor); 
            CSCALE(k2, mBackground, fogcolor); 
            CCADD(surfcolor, fogcolor, Ci);
        }
             
        if(Ci.r < 0) Ci.r = 0; else if(Ci.r > 1) Ci.r = 1;
        if(Ci.g < 0) Ci.g = 0; else if(Ci.g > 1) Ci.g = 1;
        if(Ci.b < 0) Ci.b = 0; else if(Ci.b > 1) Ci.b = 1;
        *(MgColor *)cs = Ci;
        cs->a = c->a;
    }
    return 0;
}
//--

#endif


//++MgContext::Cotransform [dpusbotgpsn,mgshade.c]
/*
 * Transform a vector covariantly
 */
void MgContext::Cotransform(register Transform3 *Tinv,
                            register Point3 *in, Point3 *out)
{
    out->x = Tinv->D.M[0][0]*in->x + Tinv->D.M[0][1]*in->y + Tinv->D.M[0][2]*in->z;
    out->y = Tinv->D.M[1][0]*in->x + Tinv->D.M[1][1]*in->y + Tinv->D.M[1][2]*in->z;
    out->z = Tinv->D.M[2][0]*in->x + Tinv->D.M[2][1]*in->y + Tinv->D.M[2][2]*in->z;
}
//--


