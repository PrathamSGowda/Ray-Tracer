#ifndef VEC3_H
#define VEC3_H

typedef struct vec3
{
    double e[3];
}vec3;

/*
    a point and a vector both store 3 elements but they represent different things
    and a colour represents r,g,b values so we can use the same structure but just 
    typedef it with a different name
*/

typedef vec3 point3;
typedef vec3 colour;

vec3 vec3_zero();
vec3 vec3_create(double e0, double e1, double e2);
vec3 vec3_neg(vec3 v);

void vec3_add_assign(vec3 *a, vec3 b);
void vec3_mul_assign(vec3 *v, double t);
void vec3_div_assign(vec3 *v, double t);

double vec3_length_squared(vec3 v);
double vec3_length(vec3 v);

void vec3_print(vec3 v);

vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 a, vec3 b);
vec3 vec3_scale(vec3 v, double t);
vec3 vec3_div(vec3 v, double t);

double vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
vec3 vec3_unit(vec3 v);

#endif