#include "vec3.h"
#include "ray.h"

ray ray_create(point3 origin, vec3 direction)
{
    ray r;
    r.origin = origin;
    r.dir = direction;
    return r;
}

point3 ray_at(ray r, double t)
{
    return vec3_add(r.origin,vec3_scale(r.dir,t)); // P(t) = A + tb
}