/*Test Function provided*/


#include "Test.h"


int AutoTest(void) {
    int result;
    const char fname[SLEN] = "EH";
    const char overlayImgName[SLEN] = "balloon";

    IMAGE *image = NULL;
    image = LoadImage(fname);
    if (! image) return 11;
    image = Negative(image);
    if (! image) return 12;
    result = SaveImage("negative", image);
    if (result) return result;
#ifdef DEBUG
    printf("Negative tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 13;
    image = ColorFilter(image, CF_TARGET_R, CF_TARGET_G, CF_TARGET_B, CF_THRESHOLD, CF_REPLACED_R, CF_REPLACED_G, CF_REPLACED_B);
    if (! image) return 14;
    result = SaveImage("colorfilter", image);
    if (result) return result;
#ifdef DEBUG
    printf("Color Filter tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 15;
    image = Edge(image);
    if (! image) return 16;
    result = SaveImage("edge", image);
    if (result) return result;
#ifdef DEBUG
    printf("Edge Detection tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 17;
    image = HFlip(image);
    if (! image) return 18;
    result = SaveImage("hflip", image);
    if (result) return result;
#ifdef DEBUG
    printf("HFlip tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 19;
    image = Vmirror(image);
    if (! image) return 20;
    result = SaveImage("vmirror", image);
    if (result) return result;
#ifdef DEBUG
    printf("Vmirror tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 21;
    image = Zoom(image);
    if (! image) return 22;
    result = SaveImage("zoom", image);
    if (result) return result;
#ifdef DEBUG
    printf("Zoom tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 23;
    image = AddNoise(image, NOISE_PERCENTAGE);
    if (! image) return 24;
    result = SaveImage("noise", image);
    if (result) return result;
#ifdef DEBUG
    printf("AddNoise tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 25;
    image = Shuffle(image);
    if (! image) return 26;
    result = SaveImage("shuffle", image);
    if (result) return result;
#ifdef DEBUG
    printf("Shuffle tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 27;
    image = Posterize(image, 6, 7, 8);
    if (! image) return 28;
    result = SaveImage("posterize", image);
    if (result) return result;
#ifdef DEBUG
    printf("Posterize tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 29;
    IMAGE *overlayImage = LoadImage(overlayImgName);
    if (! overlayImage) return 30;
    image = Overlay(image, overlayImage, OVERLAY_X_OFFSET, OVERLAY_Y_OFFSET,
            OVERLAY_BG_R, OVERLAY_BG_G, OVERLAY_BG_B);
    DeleteImage(overlayImage);
    overlayImage = NULL;
    if (! image) return 31;
    result = SaveImage("overlay", image);
    if (result) return result;
#ifdef DEBUG
    printf("Overlay tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 32;
    image = Rotate(image, ROTATED_DEGREE);
    if (! image) return 33;
    result = SaveImage("rotate", image);
    if (result) return result;
#ifdef DEBUG
    printf("Rotate tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 34;
    image = Crop(image, CROP_X, CROP_Y, CROP_WIDTH, CROP_HEIGHT);
    if (! image) return 35;
    result = SaveImage("crop", image);
    if (result) return result;
#ifdef DEBUG
    printf("Crop tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 36;
    image = Resize(image, SMALL_RESIZE_PERCENTAGE);
    if (! image) return 37;
    result = SaveImage("smallresize", image);
    if (result) return result;
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 38;
    image = Resize(image, BIG_RESIZE_PERCENTAGE);
    if (! image) return 39;
    result = SaveImage("bigresize", image);
    if (result) return result;
#ifdef DEBUG
    printf("Resize tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 40;
    image = MetalCircle(image, CIRCLE_CENTER_X, CIRCLE_CENTER_Y, CIRCLE_OUTER_RADIUS, CIRCLE_BORDER_WIDTH);
    if (! image) return 41;
    result = SaveImage("circle", image);
    if (result) return result;
#ifdef DEBUG
    printf("MetalCircle tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;
    return 0; /* success! */
}
                                                                                                                                               
