#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include "vec3.h"
#include "ray.h"

typedef struct
{
    point3 p; // Point where the ray hit
    vec3 normal; // Surface normal at the hit point
    double t; // Ray parameter
    bool front_face;
}hit_record;

struct hittable;

typedef bool (*hit_function)(const struct hittable *self, ray r, double t_min,
                            double t_max, hit_record *rec);

typedef struct hittable
{
    hit_function hit;
}hittable;

// making sure the normal is always against the incoming ray
void set_face_normal(hit_record *rec, ray r, vec3 outward_normal);

#endif