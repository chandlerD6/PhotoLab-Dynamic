/*Advanced.h header file*/

#ifndef ADVANCED_H
#define ADVANCED_H
#include "Image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileIO.h"
#include <assert.h>
#include "Constants.h"
#include <time.h>
#include <math.h>

IMAGE *Shuffle(IMAGE *image);

IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

IMAGE *AddNoise(IMAGE *image, int n);

IMAGE *Overlay(IMAGE *inputImage, const IMAGE *overlayImage, int x_offset, int y_offset,
unsigned char backgroundR, unsigned char backgroundG, unsigned char backgroundB);

IMAGE *Rotate(IMAGE *image, int degree);

IMAGE *Resize(IMAGE *image, int percentage);

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H);

IMAGE *MetalCircle(IMAGE *image, int centerX, int centerY, int outerRadius,
int borderWidth);

#endif
