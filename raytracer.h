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

	void raytrace(World* world, Orthogonal* camera){
        int width = 256;
	    int height = 256;

        Color **pixelColors = new Color*[width];
        for(int i = 0; i < width; ++i) {
            pixelColors[i] = new Color[height];
        }

        for (int y=0; y<width; y++) {
            for (int x=0; x<height; x++) {
                Vector2* pictureCoordinates = new Vector2(
                    ((x + 0.5) / width ) * 2 - 1,
                    ((y + 0.5) / height ) * 2 - 1);

                Ray* ray = camera->getRayTo(pictureCoordinates);
                HitInfo* hitInfo = world->traceRay(ray);

                if(hitInfo->isHitObject()){
                    pixelColors[x][y] = hitInfo->getColor();
                }else{
                    pixelColors[x][y] = world->getBackgroundColor();
                }
            }
        }

        saveToPng(pixelColors, width, height);

        for(int i = 0; i < width; ++i) {
            delete [] pixelColors[i];
        }
        delete [] pixelColors;
	}

	void saveToPng(Color **pixelColors, int width, int height){
        FILE *fp = fopen("file2.png", "wb");
        png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop info_ptr = png_create_info_struct(png_ptr);
        png_init_io(png_ptr, fp);

        /* write header */
        png_set_IHDR(png_ptr, info_ptr, width, height,
            8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        {
            png_text title_text;
            title_text.compression = PNG_TEXT_COMPRESSION_NONE;
            title_text.key = "Title";
            title_text.text = "raytrace_picture";
            png_set_text(png_ptr, info_ptr, &title_text, 1);

            png_write_info(png_ptr, info_ptr);
        }

        png_bytep row = NULL;
        row = (png_bytep) malloc(3 * width * sizeof(png_byte));

        // Write image data
        for (int y=0 ; y<width ; y++) {
            for (int x=0 ; x<height ; x++) {
                setRGB(&(row[x*3]), pixelColors[x][y], x, y);
            }
            png_write_row(png_ptr, row);
        }

        png_write_end(png_ptr, NULL);

        finalise:
            if (fp != NULL) fclose(fp);
            if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
            if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
            if (row != NULL) free(row);
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
};

#endif
