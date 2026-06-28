#include <math.h>

#include "sphere.h"

bool sphere_hit(sphere *s, ray r, double t_min, double t_max, hit_record *rec)
{
    vec3 oc = vec3_sub(s->center, r.origin);

    double a = vec3_length_squared(r.dir);
    double h = vec3_dot(r.dir, oc);
    double c = vec3_length_squared(oc) - s->radius * s->radius;

    double discriminant = h*h - a*c;

    if (discriminant < 0)
    {
        return false;
    }

    double sqrtd = sqrt(discriminant);
    double root = (h - sqrtd) / a;

    if (root <= t_min || root >= t_max)
    {
        root = (h + sqrtd) / a;
        if (root <= t_min || root >= t_max)
        {
            return false;
        }
    }

    rec->t = root;
    rec->p = ray_at(r, rec->t);

    vec3 outward_normal = vec3_div(vec3_sub(rec->p, s->center), s->radius);
    set_face_normal(rec, r, outward_normal);

    return true;
}