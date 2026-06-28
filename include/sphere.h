#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>

#include "ray.h"
#include "vec3.h"
#include "hittable.h"

typedef struct
{
    hittable base;
    point3 center;
    double radius;
}sphere;

sphere sphere_create(point3 center, double radius);

bool sphere_hit(const struct hittable *self, ray r, double t_min, double t_max, hit_record *rec);

#endif