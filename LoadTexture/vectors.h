/* vectors.h */

#ifndef VECTORS_H
#define VECTORS_H

#include <math.h>

#define MIN(a,b)         (((a) < (b)) ? (a) : (b))
#define MAX(a,b)         (((a) > (b)) ? (a) : (b))

#define CLAMP(x,min,max) (((x)<(min)) ? (min) : (((x)>(max)) ? (max) : (x)))

/* 3D maths */
#define V3DZERO(v)      do { (v)[0] = (v)[1] = (v)[2] = 0.0; } while (0)
#define V3DSET(v,x,y,z) do { (v)[0] = (x); (v)[1] = (y); (v)[2] = (z); } while (0)
#define V3DCOPY(v1,v2)  do { (v1)[0] = (v2)[0]; (v1)[1] = (v2)[1]; (v1)[2] = (v2)[2]; } while (0)
#define V3DDOT(v1,v2)   ((v1)[0]*(v2)[0] + (v1)[1]*(v2)[1] + (v1)[2]*(v2)[2])
#define V3DLENGTH(v)    (sqrt(V3DDOT((v),(v))))
#define V3DADD(d,s1,s2) do { (d)[0] = (s1)[0] + (s2)[0]; \
                             (d)[1] = (s1)[1] + (s2)[1]; \
                             (d)[2] = (s1)[2] + (s2)[2]; } while (0)
#define V3DSUB(d,s1,s2) do { (d)[0] = (s1)[0] - (s2)[0]; \
                             (d)[1] = (s1)[1] - (s2)[1]; \
                             (d)[2] = (s1)[2] - (s2)[2]; } while (0)
#define V3DSCALE(v,s)   do { (v)[0] *= (s); (v)[1] *= (s); (v)[2] *= (s); } while (0)
#define V3DNORMALIZE(v) do { float inv_len = 1.0 / V3DLENGTH ((v)); V3DSCALE ((v), inv_len); } while (0)
#define V3DCROSS(d,s1,s2) do \
                            { \
                              float temp[3]; \
                              temp[0] = (s1[1] * s2[2]) - (s1[2] * s2[1]); \
                              temp[1] = (s1[2] * s2[0]) - (s1[0] * s2[2]); \
                              temp[2] = (s1[0] * s2[1]) - (s1[1] * s2[0]); \
                              V3DCOPY (d, temp); \
                            } \
                          while (0)

/* 4D maths */
#define V4DCOPY(v1,v2)  do { (v1)[0] = (v2)[0]; (v1)[1] = (v2)[1]; \
                             (v1)[2] = (v2)[2]; (v1)[3] = (v2)[3]; } while (0)
#define V4DDOT(v1,v2)   ((v1)[0]*(v2)[0] + (v1)[1]*(v2)[1] + (v1)[2]*(v2)[2] + (v1)[3]*(v2)[3])
#define V4DLENGTH(v)    (sqrt(V4DDOT((v),(v))))
#define V4DSCALE(v,s)   do { (v)[0] *= (s); (v)[1] *= (s); (v)[2] *= (s); (v)[3] *= (s); } while (0)
#define V4DNORMALIZE(v) do { float inv_len = 1.0 / V4DLENGTH ((v)); V4DSCALE ((v), inv_len); } while (0)

#endif

