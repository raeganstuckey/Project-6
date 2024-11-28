#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image.h"

// Function to read a PPM file and return an ImagePPM structure
ImagePPM *readPPM(const char filename[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        return NULL;
    }

    ImagePPM *image = malloc(sizeof(ImagePPM));
    if (!image) {
        fprintf(stderr, "Error: Unable to allocate memory for image\n");
        fclose(file);
        return NULL;
    }

    // Read the magic number
    fscanf(file, "%s", image->magic);
    if (strcmp(image->magic, "P3") != 0) {
        fprintf(stderr, "Error: Invalid PPM file (magic number not P3)\n");
        free(image);
        fclose(file);
        return NULL;
    }

    // Read image dimensions and max color value
    fscanf(file, "%d %d", &image->numCols, &image->numRows);
    fscanf(file, "%d", &image->maxVal);

    // Read pixel data
    for (int i = 0; i < image->numRows; i++) {
        for (int j = 0; j < image->numCols; j++) {
            fscanf(file, "%d %d %d", 
                &image->pixels[i][j].red,
                &image->pixels[i][j].green,
                &image->pixels[i][j].blue);
        }
    }

    fclose(file);
    return image;
}

// Function to write an ImagePPM to a PPM file
int writePPM(const ImagePPM *refImagePPM, const char filename[]) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file %s for writing\n", filename);
        return -1;
    }

    // Write the magic number, dimensions, and max color value
    fprintf(file, "%s\n", refImagePPM->magic);          // Magic number (P3)
    fprintf(file, "%d %d\n", refImagePPM->numCols, refImagePPM->numRows); // Dimensions
    fprintf(file, "%d\n", refImagePPM->maxVal);         // Maximum color value

    // Write pixel data row by row
    for (int i = 0; i < refImagePPM->numRows; i++) {
        for (int j = 0; j < refImagePPM->numCols; j++) {
            Pixel p = refImagePPM->pixels[i][j];
            fprintf(file, "%d %d %d ", p.red, p.green, p.blue);
        }
        fprintf(file, "\n"); // Newline after each row
    }

    fclose(file);
    return 0;
}



// Function to copy an image
ImagePPM *copyPPM(const ImagePPM *refImagePPM) {
    if (!refImagePPM) return NULL;

    // Allocate memory for a new ImagePPM
    ImagePPM *newImage = malloc(sizeof(ImagePPM));
    if (!newImage) return NULL;

    // Copy metadata
    newImage->numRows = refImagePPM->numRows;
    newImage->numCols = refImagePPM->numCols;
    newImage->maxVal = refImagePPM->maxVal;

    // Copy pixel data
    for (int i = 0; i < refImagePPM->numRows; i++) {
        for (int j = 0; j < refImagePPM->numCols; j++) {
            newImage->pixels[i][j] = refImagePPM->pixels[i][j];
        }
    }

    return newImage;
}

// Function to apply a sepia filter
ImagePPM *convertToSepia(const ImagePPM *refImagePPM) {
    if (!refImagePPM) return NULL;

    ImagePPM *sepiaImage = copyPPM(refImagePPM);
    if (!sepiaImage) return NULL;

    for (int i = 0; i < sepiaImage->numRows; i++) {
        for (int j = 0; j < sepiaImage->numCols; j++) {
            Pixel *p = &sepiaImage->pixels[i][j];
            int originalRed = p->red;
            int originalGreen = p->green;
            int originalBlue = p->blue;

            // Sepia tone formula with clamping
            p->red = fmin(refImagePPM->maxVal, (0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue));
            p->green = fmin(refImagePPM->maxVal, (0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue));
            p->blue = fmin(refImagePPM->maxVal, (0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue));
        }
    }

    return sepiaImage;
}


// Function to grow an image by a factor of 2
ImagePPM *growPPM(const ImagePPM *refImagePPM) {
    if (!refImagePPM) return NULL;

    int newRows = refImagePPM->numRows * 2;
    int newCols = refImagePPM->numCols * 2;

    ImagePPM *grownImage = malloc(sizeof(ImagePPM));
    if (!grownImage) return NULL;

    // Set new metadata
    grownImage->numRows = newRows;
    grownImage->numCols = newCols;
    grownImage->maxVal = refImagePPM->maxVal;
    strcpy(grownImage->magic, refImagePPM->magic);

    // Expand pixel data
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            grownImage->pixels[i][j] = refImagePPM->pixels[i / 2][j / 2];
        }
    }

    return grownImage;
}


// Free the memory for an ImagePPM
void freePPM(ImagePPM *refImagePPM) {
    if (!refImagePPM) return;

    // No dynamic allocation for pixels (static array), only free the structure itself
    free(refImagePPM);
}
