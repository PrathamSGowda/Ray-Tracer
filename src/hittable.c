#include "hittable.h"

void set_face_normal(hit_record *rec, ray r, vec3 outward_normal)
{
    rec -> front_face = vec3_dot(r.dir, outward_normal) < 0; // ray is outside normal
    if(rec -> front_face)
    {
        rec -> normal = outward_normal;
    }
    else
    {
        rec -> normal = vec3_neg(outward_normal);
    }
}