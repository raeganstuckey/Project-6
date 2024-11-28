#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

int main(int argc, char **argv) {
	if (argc != 4) {
		printf("Usage: %s copy input.ppm output.ppm\n", argv[0]);
		printf("       %s sepia input.ppm output.ppm\n", argv[0]);
		printf("       %s grow input.ppm output.ppm\n", argv[0]);
		return 1;
	}

	char *command = argv[1];
	char *inputFilename = argv[2];
	char *outputFilename = argv[3];

	if (strcmp(command, "copy") == 0) {
		ImagePPM *refImagePPM = readPPM(inputFilename);
		if (refImagePPM == NULL) {
			printf("Unable to read the PPM file: %s\n", inputFilename);
			return 2;
		}
		int isSuccess = writePPM(refImagePPM, outputFilename);
		if (!isSuccess) {
			printf("Unable to write to the file: %s\n", outputFilename);
			freePPM(refImagePPM);
			return 3;
		}
		freePPM(refImagePPM);
	}
	else if (strcmp(command, "sepia") == 0) {
		ImagePPM *refOrig = readPPM(inputFilename);
		if (refOrig == NULL) {
			printf("Unable to read the PPM file: %s\n", inputFilename);
			return 4;
		}
		ImagePPM *refSepia = convertToSepia(refOrig);
		int isSuccess = writePPM(refSepia, outputFilename);
		if (!isSuccess) {
			printf("Unable to write to the file: %s\n", outputFilename);
			freePPM(refOrig);
			freePPM(refSepia);
			return 5;
		}
		freePPM(refOrig);
		freePPM(refSepia);
	}
	else if (strcmp(command, "grow") == 0) {
		ImagePPM *refOrig = readPPM(inputFilename);
		if (refOrig == NULL) {
			printf("Unable to read the PGM file: %s\n", inputFilename);
			return 6;
		}
		ImagePPM *refGrow = growPPM(refOrig);
		int isSuccess = writePPM(refGrow, outputFilename);
		if (!isSuccess) {
			printf("Unable to write to the file: %s\n", outputFilename);
			freePPM(refOrig);
			freePPM(refGrow);
			return 7;
		}
		freePPM(refOrig);
		freePPM(refGrow);
	}
	else {
	   printf("Unrecognized command\n");
	   return 8;
	}

	return 0;
}
