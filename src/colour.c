#include <stdio.h>

#include "colour.h"

// writes data of a pixel into the ppm file
void write_colour(FILE *fp, colour pixel_colour)
{
    double r = pixel_colour.e[0];
    double g = pixel_colour.e[1];
    double b = pixel_colour.e[2];

    int ir = (int)(255.999*r);
    int ig = (int)(255.999*g);
    int ib = (int)(255.999*b);

    fprintf(fp, "%d %d %d\n",ir,ig,ib);
}