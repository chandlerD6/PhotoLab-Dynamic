/*Advanced functions by Chandler Ditolla*/



#include "Advanced.h"

/* Shuffle an image */
IMAGE *Shuffle(IMAGE *image)
{
        assert(image);
        /* Generate 25 different integers in the range from 0 to 24 */
        srand(time(NULL));
        int sequence[25];
        int i,j;
        IMAGE *temp = NULL;
        temp = CreateImage(image->Width, image->Height);
        assert(temp);

        for (i = 0; i < 25; i++) {
                int count;
                do {
                        /* sequence[i] is a random number from 0 through 24 */
                        sequence[i] = rand() % 25;

                        /* Assume that sequence[i] is unique */
                        count = 0;

                        /* Check whether sequence[i] is the same as previous numbers */
                        for (j = 0; j < i; j++) {
                                if (sequence[j] == sequence[i]) {
                                        count = 1;
                                        break;
                                }
                        }
                } while(count);
        }


        int height, width;
        int block_width = image->Width / 5;
        int block_height = image->Height /5;

        for(i=0; i<25; i++) {

                int target_block_height = i/5;
                int target_block_width = i%5;

                int source_block_height = sequence[i]/5;
                int source_block_width = sequence[i]%5;

                for (height=0; height<block_height; height++) {

                        for (width=0; width<block_width; width++) {

                                int source_height = (source_block_height * block_height) + height;
                                int source_width = (source_block_width * block_width) + width;

                                int target_height = (target_block_height * block_height) + height;
                                int target_width = (target_block_width * block_width) + width;

                                SetPixelR(temp, target_width, target_height, GetPixelR(image, source_width, source_height));
                                SetPixelG(temp, target_width, target_height, GetPixelG(image, source_width, source_height));
                                SetPixelB(temp, target_width, target_height, GetPixelB(image, source_width, source_height));
                        }
                }
        }

        /* overwrite the original image with the shuffled image */
        for(width=0; width<image->Width; width++) {
                for(height=0; height<image->Height; height++) {
                        SetPixelR(image, width, height, GetPixelR(temp, width, height));
                        SetPixelG(image, width, height, GetPixelG(temp, width, height));
                        SetPixelB(image, width, height, GetPixelB(temp, width, height));
                }
        }
        DeleteImage(temp);
        temp = NULL;
        return image;
}

/* Posterize an image */

IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
        assert(image);
        int x, y;
        for(x=0; x<image->Width; x++) {
                for(y=0; y<image->Height; y++) {

                        unsigned char one = 1;
                        int i;
                        for(i=0; i<rbits-1; i++) {
                                SetPixelR(image, x, y, GetPixelR(image, x, y) | one);
                                one <<= 1;
                        }
                        one = ~one;
                        SetPixelR(image, x, y, GetPixelR(image, x, y) & one);

                        one = 1;
                        for(i=0; i<gbits-1; i++) {
                                SetPixelG(image, x, y, GetPixelG(image, x, y) | one);
                                one <<= 1;
                        }
                        one = ~one;
                        SetPixelG(image, x, y, GetPixelG(image, x, y) & one);

                        one = 1;
                        for(i=0; i<bbits-1; i++) {
                                SetPixelB(image, x, y, GetPixelB(image, x, y) | one);
                                one <<= 1;
                        }
                        one = ~one;
                        SetPixelB(image, x, y, GetPixelB(image, x, y) & one);
                }
        }
        return image;
}

/* Add noise to an image */

IMAGE *AddNoise(IMAGE *image, int n)
{
        assert(image);
        int x, y, i;
        int num;
        num = ( n*image->Height*image->Width )/100;
        srand(time(NULL));

        for ( i = 0; i < num; i++ ) {
                x = ( (double)rand()/RAND_MAX )*(image->Width-1);
                y = ( (double)rand()/RAND_MAX )*(image->Height-1);
                SetPixelR(image, x, y, 255);
                SetPixelG(image, x, y, 255);
                SetPixelB(image, x, y, 255);
        }
        return image;
}

/* Overlay an image*/

IMAGE *Overlay(IMAGE *inputImage,const IMAGE *overlayImage, int x_offset, int y_offset, unsigned char backgroundR, unsigned char backgroundG, unsigned char backgroundB)
{
        assert(inputImage);
        int x, y;

        for (y = y_offset; y < y_offset + overlayImage->Height; y++){
                for(x = x_offset; x < x_offset + overlayImage->Width; x++){
                        if( abs(GetPixelR(overlayImage, x - x_offset, y - y_offset) - backgroundR) <= 5
                            && abs(GetPixelG(overlayImage, x - x_offset, y - y_offset) - backgroundG) <= 5
                            && abs(GetPixelB(overlayImage, x - x_offset, y - y_offset) - backgroundB) <= 5)
                        {
                                continue;

                        }
                        else{
                                SetPixelR(inputImage, x, y, GetPixelR(overlayImage, x - x_offset, y - y_offset));
                                SetPixelG(inputImage, x, y, GetPixelG(overlayImage, x - x_offset, y - y_offset));
                                SetPixelB(inputImage, x, y, GetPixelB(overlayImage, x - x_offset, y - y_offset));
                        }
                }
        }
        return inputImage;



}

/* Rotate an image*/

IMAGE *Rotate(IMAGE *image, int degree){

        assert(image);
        int x, y;
        IMAGE *temp = NULL;
        temp = CreateImage(image->Width, image->Height);
        assert(temp);

        for( y = 0; y < image->Height; y++){
                for(x = 0; x < image->Width; x++){
                        SetPixelR(temp, x, y, GetPixelR(image, x, y));
                        SetPixelG(temp, x, y, GetPixelG(image, x, y));
                        SetPixelB(temp, x, y, GetPixelB(image, x, y));
                }
        }

        if(degree == 90){
                int newwidth = image->Height, newheight = image->Width;

                DeleteImage(image);
                image = NULL;
                image = CreateImage(newwidth, newheight);
                assert(image);

                for(y = 0; y < newheight; y++){
                        for(x = 0; x < newwidth; x++){
                                SetPixelR(image, newwidth - x - 1, y, GetPixelR(temp, y, x));
                                SetPixelG(image, newwidth - x - 1, y, GetPixelG(temp, y, x));
                                SetPixelB(image, newwidth - x - 1, y, GetPixelB(temp, y, x));

                        }
                }
        }

        if(degree == 180){
                int newwidth = image->Width, newheight = image->Height;

                for(y = 0; y < newheight; y++){
                        for(x = 0; x < newwidth; x++){
                                SetPixelR(image, newwidth - x -1, newheight - y -1, GetPixelR(temp, x, y));
                                SetPixelG(image, newwidth - x -1, newheight - y -1, GetPixelG(temp, x, y));
                                SetPixelB(image, newwidth - x -1, newheight - y -1, GetPixelB(temp, x, y));

                        }
                }

        }

        if(degree == 270){
                int newwidth = image->Height, newheight = image->Width;

                DeleteImage(image);
                image = NULL;
                image = CreateImage(newwidth, newheight);
                assert(image);

                for(y = 0; y < newheight; y++){
                        for(x = 0; x < newwidth; x++){
                                SetPixelR(image, x, newheight - y - 1, GetPixelR(temp, y, x));
                                SetPixelG(image, x, newheight - y - 1, GetPixelG(temp, y, x));
                                SetPixelB(image, x, newheight - y - 1, GetPixelB(temp, y, x));

                        }
                }
        }
        DeleteImage(temp);
        temp = NULL;
        return image;
}

/* Crop an image*/

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H){

        assert(image);
        int i, j, tempx = x;
        IMAGE *temp = NULL;
        temp = CreateImage(W, H);
        assert(temp);

        for(i = 0; i < H; i++){
                for(j = 0; j < W; j++){
                        SetPixelR(temp, j, i, GetPixelR(image, x, y));
                        SetPixelG(temp, j, i, GetPixelG(image, x, y));
                        SetPixelB(temp, j, i, GetPixelB(image, x, y));
                        x++;
                }
                x = tempx;
                y++;
        }
        DeleteImage(image);
        image = NULL;
        image = CreateImage(W, H);
        assert(image);

        for(i = 0; i < H; i++){
                for(j = 0; j < W; j++){
                        SetPixelR(image, j, i, GetPixelR(temp, j, i));
                        SetPixelG(image, j, i, GetPixelG(temp, j, i));
                        SetPixelB(image, j, i, GetPixelB(temp, j, i));
                }
        }
        DeleteImage(temp);
        temp = NULL;
        return image;
}

/* Resize an image*/

IMAGE *Resize(IMAGE *image, int percentage){

        assert(image);
        int x, y, newwidth, newheight, tempwidth, tempheight;
        IMAGE *temp = NULL;
        temp = CreateImage(image->Width, image->Height);
        assert(temp);

        newwidth = image->Width * (percentage / 100.00);
        newheight = image->Height * (percentage / 100.00);

        for( y = 0; y < image->Height; y++){
                for( x = 0; x < image->Width; x++){
                        SetPixelR(temp, x, y, GetPixelR(image, x, y));
                        SetPixelG(temp, x, y, GetPixelG(image, x, y));
                        SetPixelB(temp, x, y, GetPixelB(image, x, y));
                }
        }

        if (percentage > 100){
                DeleteImage(image);
                image = NULL;
                image = CreateImage(newwidth, newheight);
                assert(image);

                for( y = 0; y < newheight; y++){
                        for( x = 0; x < newwidth; x++){
                                SetPixelR(image, x, y, GetPixelR(temp, (x * 100)/percentage, (y * 100)/percentage));
                                SetPixelG(image, x, y, GetPixelG(temp, (x * 100)/percentage, (y * 100)/percentage));
                                SetPixelB(image, x, y, GetPixelB(temp, (x * 100)/percentage, (y * 100)/percentage));

                        }
                }
                                                                                                                                            

        }

        if (percentage < 100){
                unsigned char Rhold, Ghold, Bhold;
                tempwidth = image->Width;
                tempheight = image->Height;
                DeleteImage(image);
                image = NULL;
                image = CreateImage(newwidth, newheight);
                assert(image);

                for( y = 0; y < newheight; y++){
                        for( x = 0; x < newwidth; x++){

                                Rhold = (GetPixelR(temp, ((x * 100) / percentage), ((y * 100) / percentage)) + GetPixelR(temp, ((x * 100) / percentage), (((y + 1) * 100) / percentage) - 1) + GetPixelR(temp, (((x + 1) *100) / percentage) - 1, ((y * 100) / percentage)) + GetPixelR(temp, (((x + 1) * 100) / percentage) - 1, (((y + 1) * 100) / percentage) - 1))/4;
                                Ghold = (GetPixelG(temp, ((x * 100) / percentage), ((y * 100) / percentage)) + GetPixelG(temp, ((x * 100) / percentage), (((y + 1) * 100) / percentage) - 1) + GetPixelG(temp, (((x + 1) *100) / percentage) - 1, ((y * 100) / percentage)) + GetPixelG(temp, (((x + 1) * 100) / percentage) - 1, (((y + 1) * 100) / percentage) - 1))/4;
                                Bhold = (GetPixelB(temp, ((x * 100) / percentage), ((y * 100) / percentage)) + GetPixelB(temp, ((x * 100) / percentage), (((y + 1) * 100) / percentage) - 1) + GetPixelB(temp, (((x + 1) *100) / percentage) - 1, ((y * 100) / percentage)) + GetPixelB(temp, (((x + 1) * 100) / percentage) - 1, (((y + 1) * 100) / percentage) - 1))/4;

                                SetPixelR(image, x, y, Rhold);
                                SetPixelG(image, x, y, Ghold);
                                SetPixelB(image, x, y, Bhold);
                        }
                }
        }
        DeleteImage(temp);
        temp = NULL;
        return image;
}

/*Encircle an image*/

IMAGE *MetalCircle(IMAGE *image, int centerX, int centerY, int outerRadius, int borderWidth){

        assert(image);
        int x, y, newwidth, newheight;
        IMAGE *temp = NULL;
        temp = CreateImage(image->Width, image->Height);
                                                                                                                                             
        assert(temp);

        for( y = 0; y < image->Height; y++){
                for( x = 0; x < image->Width; x++){
                        SetPixelR(temp, x, y, GetPixelR(image, x, y));
                        SetPixelG(temp, x, y, GetPixelG(image, x, y));
                        SetPixelB(temp, x, y, GetPixelB(image, x, y));
                }
        }

        newwidth = (2 * outerRadius) + 1;
        newheight = (2 * outerRadius) + 1;
        DeleteImage(image);
        image = NULL;
        image = CreateImage(newwidth, newheight);
        assert(image);

        for(y = 0; y < newheight; y++){
                for(x = 0; x < newwidth; x++){

                        if( sqrt(pow(x - outerRadius, 2)+ pow(y - outerRadius, 2)) >= outerRadius){
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                        else if( sqrt(pow(x - outerRadius, 2)+ pow(y - outerRadius, 2)) >= outerRadius - borderWidth){
                                SetPixelR(image, x, y, 224);
                                SetPixelG(image, x, y, 223);
                                SetPixelB(image, x, y, 219);
                        }
                        else
                        {
                                SetPixelR(image, x, y, GetPixelR(temp, centerX-outerRadius + x, centerY-outerRadius +y));
                                SetPixelG(image, x, y, GetPixelG(temp, centerX-outerRadius + x, centerY-outerRadius +y));
                                SetPixelB(image, x, y, GetPixelB(temp, centerX-outerRadius + x, centerY-outerRadius +y));
                        }
                }
        }
        DeleteImage(temp);
        temp = NULL;
        return image;
}
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */

