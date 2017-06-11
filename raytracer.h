#ifndef RAYTRACER
#define RAYTRACER

#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include "orthogonalCamera.h"
#include <math.h>

class Raytracer {

public:
	Raytracer() {
	}

	void raytrace(World* world, Orthogonal* camera) {
//	    const int dimx = 255, dimy = 255;
//        int i, j;
//        FILE *fp = fopen("first.bmp", "wb"); /* b - binary mode */
//
//        (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
//
//		for (j = 0; j < dimy; ++j)
//        {
//            for (i = 0; i < dimx; ++i)
//            {
//                static unsigned char color[3];
//                color[0] = i % 256;  /* red */
//                color[1] = j % 256;  /* green */
//                color[2] = (i * j) % 256;  /* blue */
//                (void) fwrite(color, 1, 3, fp);
//            }
//        }
//      (void) fclose(fp);

        FILE *fp = fopen("file.png", "wb");
        png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        png_infop info_ptr = png_create_info_struct(png_ptr);
        png_init_io(png_ptr, fp);

        /* write header */
        png_set_IHDR(png_ptr, info_ptr, 256, 256,
            8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);

        /* write bytes */
        png_bytep * row_pointers;
        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * 256);
        for (int y=0; y<256; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        for (int i=0; i<256; i++){
            png_byte* row = row_pointers[i];
            for (int j=0; j<256; j++){
                png_byte* ptr = &(row[j*4]);
                printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                               i, j, ptr[0], ptr[1], ptr[2], ptr[3]);

                ptr[0] = 100;
                ptr[1] = 200;
            }
        }

        png_write_image(png_ptr, row_pointers);
        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
        for (int y=0; y<256; y++) free(row_pointers[y]);
        free(row_pointers);

        fclose(fp);
        printf("version 1");
	}

	void raytrace2(World* world, Orthogonal* camera){
	    int width = 256;
	    int height = 256;

        FILE *fp = fopen("file2.png", "wb");
        png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop info_ptr = png_create_info_struct(png_ptr);
        png_init_io(png_ptr, fp);

        /* write header */
        png_set_IHDR(png_ptr, info_ptr, width, height,
            8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

          png_text title_text;
          title_text.compression = PNG_TEXT_COMPRESSION_NONE;
          title_text.key = "Title";
          title_text.text = "Tytul";
          png_set_text(png_ptr, info_ptr, &title_text, 1);

        png_write_info(png_ptr, info_ptr);

        png_bytep row = NULL;
        row = (png_bytep) malloc(3 * width * sizeof(png_byte));

        float *buffer = createMandelbrotImage(width, height, -0.802, -0.177, 0.011, 110);

       // Write image data
       int x, y;
       for (y=0 ; y<width ; y++) {
          for (x=0 ; x<height ; x++) {
             Vector2* pictureCoordinates = new Vector2(
                    ((x + 0.5) / width ) * 2 - 1,
                    ((y + 0.5) / height ) * 2 - 1);

             Ray* ray = camera->getRayTo(pictureCoordinates);
             HitInfo* hitInfo = world->traceRay(ray);

             Color color;
             if(hitInfo->isHitObject()){
                color = hitInfo->getColor();
             }else{
                 color = world->getBackgroundColor();
             }

//             setRGB(&(row[x*3]), buffer[y*height + x]);
             setRGB(&(row[x*3]), color, x, y);
          }
          png_write_row(png_ptr, row);
       }

       // End write
       png_write_end(png_ptr, NULL);

        finalise:
        if (fp != NULL) fclose(fp);
        if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
        if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
        if (row != NULL) free(row);

       free(buffer);
	}

	void setRGB(png_byte *ptr, float val)
    {
        int v = (int)(val * 767);
        if (v < 0) v = 0;
        if (v > 767) v = 767;
        int offset = v % 256;

        if (v<256) {
            ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
        }
        else if (v<512) {
            ptr[0] = 0; ptr[1] = offset; ptr[2] = 255-offset;
        }
        else {
            ptr[0] = offset; ptr[1] = 255-offset; ptr[2] = 0;
        }
        ptr[0] = 40; ptr[1] = 100; ptr[2] = 100;
    }

    void setRGB(png_byte *ptr, Color color, int x, int y)
    {
        ptr[0] = ( int ) floor( color.getR() * 255.0 );
        ptr[1] = ( int ) floor( color.getG() * 255.0 );
        ptr[2] = ( int ) floor( color.getB() * 255.0 );

        int temp=0;
        if(ptr[0]<=temp && ptr[1]<=temp && ptr[2]<=0){
            printf("sss on %d, %d\n", x, y);
        }
    }

    float *createMandelbrotImage(int width, int height, float xS, float yS, float rad, int maxIteration)
    {
        float *buffer = (float *) malloc(width * height * sizeof(float));
        if (buffer == NULL) {
            fprintf(stderr, "Could not create image buffer\n");
            return NULL;
        }

        // Create Mandelbrot set image

        int xPos, yPos;
        float minMu = maxIteration;
        float maxMu = 0;

        for (yPos=0 ; yPos<height ; yPos++)
        {
            float yP = (yS-rad) + (2.0f*rad/height)*yPos;

            for (xPos=0 ; xPos<width ; xPos++)
            {
                float xP = (xS-rad) + (2.0f*rad/width)*xPos;

                int iteration = 0;
                float x = 0;
                float y = 0;

                while (x*x + y*y <= 4 && iteration < maxIteration)
                {
                    float tmp = x*x - y*y + xP;
                    y = 2*x*y + yP;
                    x = tmp;
                    iteration++;
                }

                if (iteration < maxIteration) {
                    float modZ = sqrt(x*x + y*y);
                    float mu = iteration - (log(log(modZ))) / log(2);
                    if (mu > maxMu) maxMu = mu;
                    if (mu < minMu) minMu = mu;
                    buffer[yPos * width + xPos] = mu;
                }
                else {
                    buffer[yPos * width + xPos] = 0;
                }
            }
        }

        // Scale buffer values between 0 and 1
        int count = width * height;
        while (count) {
            count --;
            buffer[count] = (buffer[count] - minMu) / (maxMu - minMu);
        }

        return buffer;
    }

};

#endif
