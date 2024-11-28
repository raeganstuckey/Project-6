#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef struct _pixel {
    int red;
    int green;
    int blue;
} Pixel;

#define MAX_PIXEL_DIM 10000

typedef struct _imagePPM {
    char magic[3]; // magic P3
    int numRows; // number of rows
    int numCols; // number of columns
    int maxVal; // max value of pixel colors
    Pixel pixels[MAX_PIXEL_DIM][MAX_PIXEL_DIM]; // actual pixel data, a 2D array
} ImagePPM;

ImagePPM *readPPM(const char filename[]);
int writePPM(const ImagePPM *refImagePPM, const char filename[]);
void freePPM(ImagePPM *refImagePPM);

ImagePPM *convertToSepia(const ImagePPM *refImagePPM);
ImagePPM *growPPM(const ImagePPM *refImagePPM);

#endif
