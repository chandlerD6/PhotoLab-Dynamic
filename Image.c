#include "Image.h"



unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y){

        assert(image);
        unsigned char r;
        r = image->R[y*image->Width + x];
        return r;

}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y){

        assert(image);
        unsigned char g;
        g = image->G[y*image->Width + x];
        return g;
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y){

        assert(image);
        unsigned char b;
        b = image->B[y*image->Width + x];
        return b;
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){

        assert(image);
        image->R[y*image->Width + x] = r;

}

/* Set the G intensity of pixel (x, y) in image to g */


        assert(image);
        unsigned char b;
        b = image->B[y*image->Width + x];
        return b;
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){

        assert(image);
        image->R[y*image->Width + x] = r;

}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){

        assert(image);
        image->G[y*image->Width + x] = g;

}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){

        assert(image);
        image->B[y*image->Width + x] = b;

}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height){

        IMAGE *image = NULL;

        image = malloc(sizeof(IMAGE));

        if(image == NULL){
                return NULL;
        }

        image->Height = Height;
        image->Width = Width;

        image->R = malloc(sizeof(image->R) * Width *Height);

        if(image->R == NULL){
                free(image);
                return NULL;
        }

        image->G = malloc(sizeof(image->G) * Width *Height);

        if(image->G == NULL){
                free(image->R);
                free(image);
                return NULL;
        }

        image->B = malloc(sizeof(image->B) *Width *Height);

        if(image->B == NULL){
                free(image->R);
                free(image->G);
                free(image);
                return NULL;
        }

        return image;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image){
        assert(image);
        free(image->R);
        image->R = NULL;
        free(image->G);
        image->G = NULL;
        free(image->B);
        image->B = NULL;
        free(image);
        image = NULL;

}
