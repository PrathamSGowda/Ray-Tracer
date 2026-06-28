#include <stdio.h>
#include <math.h>

#include "vec3.h"
#include "colour.h"
#include "ray.h"

double hit_sphere(point3 center, double radius, ray r)
{
    vec3 oc = vec3_sub(center,r.origin); // vector to sphere center from ray origin
    
    double a = vec3_dot(r.dir,r.dir); // coefficient of t^2
    double b = -2.0 * vec3_dot(r.dir,oc); // coefficient of t
    double c = vec3_dot(oc,oc) - radius*radius; // constant term

    double discriminant = b*b - 4*a*c;

    // return (discriminant >= 0); // condition implies point lies on or inside sphere

    if(discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0 * a);
        // we return the smaller root because it is the
        // first intersection or else we will be taking
        // point which is on the back and cant be seen
    }

}

colour ray_colour(ray r) // returns the color for a given scene ray
{
    // colour c = {{0,0,0}}; // black image

    /*
    // sphere
    if(hit_sphere(vec3_create(0,0,-1),0.5,r))
    {
        colour pink = {{1.0,0.75,0.79}};
        return pink;
    }
    */

    // colour map for normal vectors of sphere
    double t = hit_sphere(vec3_create(0,0,-1),0.5,r);
    if(t > 0.0)
    {
        vec3 N = vec3_unit(vec3_sub(ray_at(r,t), vec3_create(0,0,-1))); // normal vector to POI from sphere center
        colour map = {{N.e[0] + 1, N.e[1] + 1, N.e[2] + 1}};
        return vec3_scale(map, 0.5);
    }

    // vertical gradient
    vec3 unit_direction = vec3_unit(r.dir);
    double a = 0.5 * (unit_direction.e[1] + 1.0);
    colour white = {{1.0,1.0,1.0}};
    colour blue = {{0.1,0.7,0.8}};
    return vec3_add(vec3_scale(white, 1.0-a), vec3_scale(blue, a));
}

int main()
{
    /*
    int image_width = 256;
    int image_height = 256;
    */

    // Image properties
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio); // aspect ratio = width/height

    // making sure that the image height is atleast 1
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera properties
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / image_height);
    point3 camera_center = vec3_zero(); // center is at (0,0,0)

    // Viewport vectors
    vec3 viewport_u = vec3_create(viewport_width,0,0); // vector measuring width of viewport (left to right)
    vec3 viewport_v = vec3_create(0,-viewport_height,0); // vector measuring height of viewport (top to bottom)

    // distance between adjacent pixels
    vec3 pixel_delta_u = vec3_div(viewport_u, image_width);
    vec3 pixel_delta_v = vec3_div(viewport_v, image_height);

    /* 
        upper left corner of the viewport (Q):
        To find this we move a distance of focal length in -z direction
        then move in -x direction a distance of u/2 to reach left edge
        then move in +y direction a distance of v/2 to reach point Q.
    */
    point3 viewport_upper_left = vec3_sub(vec3_sub(vec3_sub(camera_center,vec3_create(0,0,focal_length)),
                                 vec3_div(viewport_u,2)),vec3_div(viewport_v,2));

    /*
        location of center of pixel P(0,0):
        To find this we first find the diagonal vector by adding u and v
        then we find half of this diagonal vector by scalling it to 0.5
        and to this we add Q vector,
    */
    point3 pixel00_loc = vec3_add(viewport_upper_left,vec3_scale(vec3_add(pixel_delta_u,pixel_delta_v),0.5));

    FILE *fp = fopen("image4.ppm","w");

    if(fp==NULL)
    {
        return 1;
    }

    // PPM format (portable pixmap format)
    fprintf(fp,"P3\n"); // the colours are in ASCII human readable format
    fprintf(fp,"%d %d\n",image_width,image_height); // max columns and max rows
    fprintf(fp,"255\n"); // max colour value [0,255]

    // render
    for(int i=0; i<image_height; i++) // rows
    {
        printf("\rRows remaining: %d  ",image_height-(i+1)); // progress bar to track the number of rows remaining in render
        // carriage return \r is used to rewrite on the same line in the terminal
        fflush(stdout);
        for(int j=0; j<image_width; j++) // columns
        {
            /* GRADIENT IMAGE CODE:
            double r = (double)j / (image_width-1); // intensity of red increases left to right
            double g = (double)i / (image_height-1); // intensity of green increases top to bottom
            double b = 1.0;

            // // scaling the decimal values to integral values between 0 to 255
            // int ir = (int)(255*r);
            // int ig = (int)(255*g);
            // int ib = (int)(255*b);

            // // printing R G B values for the respective pixel
            // fprintf(fp,"%d %d %d\n",ir,ig,ib);

            colour pixel_colour = {{r,g,b}};
            write_colour(fp,pixel_colour);
            */

            // calculating center of current pixel
            point3 pixel_center = vec3_add(vec3_add(pixel00_loc,vec3_scale(pixel_delta_u,j)),vec3_scale(pixel_delta_v,i));

            vec3 ray_direction = vec3_sub(pixel_center,camera_center); // vector pointing to pixel from camera
            ray r = ray_create(camera_center,ray_direction);

            colour pixel_colour = ray_colour(r);
            write_colour(fp,pixel_colour);
        }
    }
    printf("\nRender completed\n");
    fclose(fp);
    return 0;
}