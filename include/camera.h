#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>

#include "vec3.h"
#include "hittable_list.h"

typedef struct camera
{
    // image properties
    double aspect_ratio;
    int image_width;
    int image_height;
    int samples_per_pixel;

    // camera properties
    double focal_length;
    point3 camera_center;

    // viewport properties
    double viewport_height;
    double viewport_width;
    vec3 viewport_u;
    vec3 viewport_v;

    // distance between adjacent pixels
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    // center of the top-left pixel
    point3 pixel00_loc;

}camera;

camera camera_create(double aspect_ratio, int image_width);

void camera_render(camera *cam, const hittable_list *world, FILE *fp);


#endif