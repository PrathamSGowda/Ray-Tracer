#include <stdio.h>

int main()
{
    int image_width = 256;
    int image_height = 256;

    FILE *fp = fopen("image.ppm","w");

    if(fp==NULL)
    {
        return 1;
    }

    // PPM format (portable pixmap format)
    fprintf(fp,"P3\n"); // the colours are in ASCII human readable format
    fprintf(fp,"%d %d\n",image_width,image_height); // max columns and max rows
    fprintf(fp,"255\n"); // max colour value [0,255]

    // printing the pixels
    for(int i=0; i<image_height; i++) // rows
    {
        for(int j=0; j<image_width; j++) // columns
        {
            double r = (double)j / (image_width-1); // intensity of red increases left to right
            double g = (double)i / (image_height-1); // intensity of green increases top to bottom
            double b = 0.0;

            // scaling the decimal values to integral values between 0 to 255
            int ir = (int)(255*r);
            int ig = (int)(255*g);
            int ib = (int)(255*b);

            // printing R G B values for the respective pixel
            fprintf(fp,"%d %d %d\n",ir,ig,ib);
        }
    }
    fclose(fp);
    return 0;
}