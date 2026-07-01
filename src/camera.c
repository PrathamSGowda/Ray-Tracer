#include <stdio.h>

#include "camera.h"
#include "rtweekend.h"
#include "colour.h"

camera camera_create(double aspect_ratio, int image_width)
{
    camera cam;

    // Image properties
    cam.aspect_ratio = aspect_ratio;
    cam.image_width = image_width;
    cam.image_height = (int)(image_width / aspect_ratio);
    cam.samples_per_pixel = 100;

    if(cam.image_height < 1)
    {
        cam.image_height = 1;
    }

    // camera properties
    cam.focal_length = 1.0;
    cam.viewport_height = 2.0;
    cam.viewport_width = cam.viewport_height * ((double)cam.image_width / cam.image_height);

    cam.camera_center = vec3_zero();

    // viewport vectors
    cam.viewport_u = vec3_create(cam.viewport_width, 0, 0);
    cam.viewport_v = vec3_create(0, -cam.viewport_height, 0);

    // pixel spacing
    cam.pixel_delta_u = vec3_div(cam.viewport_u, cam.image_width);
    cam.pixel_delta_v = vec3_div(cam.viewport_v, cam.image_height);

    /* 
        upper left corner of the viewport (Q):
        To find this we move a distance of focal length in -z direction
        then move in -x direction a distance of u/2 to reach left edge
        then move in +y direction a distance of v/2 to reach point Q.
    */
    point3 viewport_upper_left = vec3_sub(vec3_sub(vec3_sub(cam.camera_center,vec3_create(0, 0, cam.focal_length)),
                                 vec3_div(cam.viewport_u, 2)), vec3_div(cam.viewport_v, 2));

    /*
        location of center of pixel P(0,0):
        To find this we first find the diagonal vector by adding u and v
        then we find half of this diagonal vector by scalling it to 0.5
        and to this we add Q vector,
    */
    cam.pixel00_loc = vec3_add(viewport_upper_left, vec3_scale(vec3_add(cam.pixel_delta_u,cam.pixel_delta_v),0.5));

    return cam;
}

point3 pixel_sample_square(camera *cam, point3 pixel_center)
{
    double px = random_double() - 0.5;
    double py = random_double() - 0.5;

    vec3 offset_u = vec3_scale(cam->pixel_delta_u, px);
    vec3 offset_v = vec3_scale(cam->pixel_delta_v, py);

    return vec3_add(pixel_center, vec3_add(offset_u,offset_v));
}

colour ray_colour(ray r, const hittable_list *world)
{
    hit_record rec;

    if(hittable_list_hit(world, r, 0.001, INFINITY, &rec))
    {
        return vec3_scale(vec3_add(rec.normal, vec3_create(1.0, 1.0, 1.0)), 0.5);
    }

    vec3 unit_direction = vec3_unit(r.dir);

    double a = 0.5 * (unit_direction.e[1] + 1.0);

    colour white = {{1.0, 1.0, 1.0}};
    colour blue  = {{0.5, 0.7, 1.0}};

    return vec3_add(vec3_scale(white, 1.0 - a), vec3_scale(blue, a));
}

void camera_render(camera *cam, const hittable_list *world, FILE *fp)
{
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", cam->image_width, cam->image_height);
    fprintf(fp, "255\n");

    for(int i = 0; i < cam->image_height; i++)
    {
        printf("\rRows remaining: %d  ", cam->image_height - (i + 1));
        fflush(stdout);

        for(int j = 0; j < cam->image_width; j++)
        {
            point3 pixel_center =vec3_add(vec3_add(cam->pixel00_loc,vec3_scale(cam->pixel_delta_u, j)), vec3_scale(cam->pixel_delta_v, i));
            point3 pixel_sample = pixel_sample_square(cam, pixel_center);

            vec3 ray_direction = vec3_sub(pixel_center, cam->camera_center);
            ray r = ray_create(cam->camera_center, ray_direction);

            colour pixel_colour = vec3_zero();
            for(int sample = 0; sample < cam->samples_per_pixel; sample++)
            {
                point3 pixel_sample = pixel_sample_square(cam, pixel_center);
                vec3 ray_direction = vec3_sub(pixel_sample, cam->camera_center);
                ray r = ray_create(cam->camera_center, ray_direction);

                pixel_colour = vec3_add(pixel_colour, ray_colour(r, world));
            }
            pixel_colour = vec3_div(pixel_colour, cam->samples_per_pixel);
            write_colour(fp, pixel_colour);
        }
    }
    printf("\nRender completed\n");
}