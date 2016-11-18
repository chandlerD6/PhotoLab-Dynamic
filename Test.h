#ifndef TEST_H
#define TEST_H
#include <stdio.h>
#include "Constants.h"
#include "Image.h"
#include "FileIO.h"
#include "Advanced.h"
#include "DIPs.h"

/* Test all DIPs */
int AutoTest(void);

/* test parameters used in AutoTest() */
/* parameters for color filter */
#define CF_TARGET_R 190
#define CF_TARGET_G 100
#define CF_TARGET_B 150
#define CF_THRESHOLD 60
#define CF_REPLACED_R 0
#define CF_REPLACED_G 0
#define CF_REPLACED_B 255

/* noise */
#define NOISE_PERCENTAGE 9

/* posterize */
#define R_BITS 6
#define G_BITS 7
#define B_BITS 8

/* overlay */
#define OVERLAY_X_OFFSET 20
#define OVERLAY_Y_OFFSET 20
#define OVERLAY_BG_R 164
#define OVERLAY_BG_G 163
#define OVERLAY_BG_B 179

/* rotate */
#define ROTATED_DEGREE 90

#define CROP_X 200
#define CROP_Y 150
#define CROP_WIDTH 400
#define CROP_HEIGHT 250

#define BIG_RESIZE_PERCENTAGE 170
#define SMALL_RESIZE_PERCENTAGE 60

#define CIRCLE_CENTER_X 320
#define CIRCLE_CENTER_Y 240
#define CIRCLE_OUTER_RADIUS 220
#define CIRCLE_BORDER_WIDTH 10

#endif /* TEST_H */
