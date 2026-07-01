#include <stdio.h>

#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"

int main(void)
{
    // create the world
    hittable_list world;
    hittable_list_init(&world);

    sphere sphere1 = sphere_create(vec3_create(0, 0, -1), 0.5);
    sphere ground = sphere_create(vec3_create(0, -100.5, -1), 100.0);

    hittable_list_add(&world, (hittable *)&sphere1);
    hittable_list_add(&world, (hittable *)&ground);

    FILE *fp = fopen("image4.ppm", "w");

    if(fp == NULL)
    {
        printf("Failed to create output file.\n");
        hittable_list_clear(&world);
        return 1;
    }

    // create the camera
    camera cam = camera_create(16.0 / 9.0, 400);

    // render the scene
    camera_render(&cam, &world, fp);

    fclose(fp);
    hittable_list_clear(&world);

    return 0;
}