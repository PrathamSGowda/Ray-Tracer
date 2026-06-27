#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray
{
    point3 origin; // ray start point
    vec3 dir; // direction of the ray
}ray;

ray ray_create(point3 origin, vec3 direction);
point3 ray_at(ray r, double t); // position of a point along the ray

#endif