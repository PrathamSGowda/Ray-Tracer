#include <stdio.h>
#include <math.h>

#include "vec3.h"

vec3 vec3_zero()
{
    vec3 v = {{0.0,0.0,0.0}};
    return v;
}

vec3 vec3_create(double e0, double e1, double e2)
{
    vec3 v = {{e0,e1,e2}};
    return v;
}

vec3 vec3_neg(vec3 v) // negates the elements of the vector
{
    vec3 res = {{-v.e[0], -v.e[1], -v.e[2]}};
    return res;
}

void vec3_add_assign(vec3 *a, vec3 b) // adds two vectors and stores new vector in the first one
{
    // pointer is used so that it modifies the original vector 
    a->e[0] += b.e[0];
    a->e[1] += b.e[1];
    a->e[2] += b.e[2];
}

void vec3_mul_assign(vec3 *v, double t) // multiplies vector with a scalar and stores it on same vector
{
    v->e[0] *= t;
    v->e[1] *= t;
    v->e[2] *= t;
}

void vec3_div_assign(vec3 *v, double t) // divides vector with a scalar and stores it in same vector
{
    vec3_mul_assign(v,1.0/t); // multiplying with reciprocal of t
}

double vec3_length_squared(vec3 v) // sqaures all the elements and adds them
{
    return v.e[0]*v.e[0] + v.e[1]*v.e[1] + v.e[2]*v.e[2];
}

double vec3_length(vec3 v) // distance of vector from origin
{
    return sqrt(vec3_length_squared(v));
}

void vec3_print(vec3 v)
{
    printf("%f %f %f\n",v.e[0],v.e[1],v.e[2]);
}

vec3 vec3_add(vec3 a, vec3 b)
{
    return vec3_create(a.e[0]+b.e[0], a.e[1]+b.e[1], a.e[2]+b.e[2]);
}

vec3 vec3_sub(vec3 a, vec3 b)
{
    return vec3_create(a.e[0]-b.e[0], a.e[1]-b.e[1], a.e[2]-b.e[2]);
}

vec3 vec3_mul(vec3 a, vec3 b)
{
    return vec3_create(a.e[0]*b.e[0], a.e[1]*b.e[1], a.e[2]*b.e[2]);
}

vec3 vec3_scale(vec3 v, double t)
{
    return vec3_create(t*v.e[0], t*v.e[1], t*v.e[2]);
}

vec3 vec3_div(vec3 v, double t)
{
    return vec3_scale(v,1.0/t);
}

double vec3_dot(vec3 a, vec3 b)
{
    return a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2];
}

vec3 vec3_cross(vec3 a, vec3 b)
{
    // expanding the cross product matrix
    return vec3_create
    (
        a.e[1] * b.e[2] - a.e[2] * b.e[1],
        a.e[2] * b.e[0] - a.e[0] * b.e[2],
        a.e[0] * b.e[1] - a.e[1] * b.e[0]
    );
}

vec3 vec3_unit(vec3 v) // unit vector of a vector
{
    return vec3_div(v,vec3_length(v));
}