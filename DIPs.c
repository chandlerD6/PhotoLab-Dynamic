/* Basic Functions by Chandler Ditolla*/


#include "DIPs.h"

/* Negative */
IMAGE *Negative(IMAGE *image)
{
        assert(image);
        int x, y;
        for( y = 0; y < image->Height; y ++ ) {
                for( x = 0; x < image->Width; x ++ ) {
                        SetPixelR(image, x, y,  255 - GetPixelR(image, x, y));
                        SetPixelG(image, x, y,  255 - GetPixelG(image, x, y));
                        SetPixelB(image, x, y,  255 - GetPixelB(image, x, y));
                }
        }
        return image;
}

/* ColorFilter */

IMAGE *ColorFilter (IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
        assert(image);
        int x, y ;
        int temp ;

        for (y=0; y<image->Height; y++) {
                for (x=0; x<image->Width; x++) {
                        if ((GetPixelR(image, x, y) <= target_r + threshold)&&
                                        (GetPixelR(image, x, y) >= target_r - threshold)&&
                                        (GetPixelG(image, x, y) <= target_g + threshold)&&
                                        (GetPixelG(image, x, y) >= target_g - threshold)&&
                                        (GetPixelB(image, x, y) <= target_b + threshold)&&
                                        (GetPixelB(image, x, y) >= target_b - threshold)) {
                                temp = replace_r;
                                SetPixelR(image, x, y,  (temp > 255)? 255 : (temp <0)? 0 : temp) ;
                                temp = replace_g;
                                SetPixelG(image, x, y,  (temp > 255)? 255 : (temp <0)? 0 : temp) ;
                                temp = replace_b;
                                SetPixelB(image, x, y, (temp > 255)? 255 : (temp <0)? 0 : temp) ;
                        }
                }
        }
        return image;
}

/* Edge */

IMAGE *Edge(IMAGE *image)
{
        assert(image);
        int x, y, m, n, a, b;
        int tmpR = 0;
        int tmpG = 0;
        int tmpB = 0;
        IMAGE *imagetmp = NULL;

        imagetmp = CreateImage(image->Width, image->Height);
        assert(imagetmp);

        for (y = 0; y < image->Height; y++) {
                for (x = 0; x < image->Width; x++) {
                        SetPixelR(imagetmp, x, y, GetPixelR(image, x, y));
                        SetPixelG(imagetmp, x, y, GetPixelG(image, x, y));
                        SetPixelB(imagetmp, x, y, GetPixelB(image, x, y));
                }
        }

        for (y = 0; y < image->Height; y++) {
                for (x = 0; x < image->Width; x++) {
                        for (n = -1; n <= 1; n++) {
                                for (m = -1; m <= 1; m++) {
                                        a = x + m;
                                        b = y + n;
                                        if (a > image->Width - 1)
                                                a = image->Width - 1;
                                        if (a < 0)
                                                a = 0;
                                        if (b > image->Height - 1)
                                                b = image->Height - 1;
                                        if (b < 0)
                                                b = 0;

                                        if ((n==0)&&(m==0)) {

                                                tmpR += 8*GetPixelR(imagetmp, a, b) ;
                                                tmpG += 8*GetPixelG(imagetmp, a, b) ;
                                                tmpB += 8*GetPixelB(imagetmp, a, b) ;
                                        } else {
                                                tmpR -= GetPixelR(imagetmp, a, b) ;
                                                tmpG -= GetPixelG(imagetmp, a, b) ;
                                                tmpB -= GetPixelB(imagetmp, a, b) ;
                                        }
                                }
                        }
                        SetPixelR(image, x, y, (tmpR>255)? 255: (tmpR<0)? 0: tmpR) ;
                        SetPixelG(image, x, y, (tmpG>255)? 255: (tmpG<0)? 0: tmpG) ;
                        SetPixelB(image, x, y, (tmpB>255)? 255: (tmpB<0)? 0: tmpB) ;
                        tmpR = tmpG = tmpB = 0;
                        if( x == 0 || y == 0 || x == image->Width - 1 || y == image->Height - 1){
                                SetPixelR(image, x, y, 0);
                                SetPixelG(image, x, y, 0);
                                SetPixelB(image, x, y, 0);
                        }
                }
        }
        DeleteImage(imagetmp);
        imagetmp = NULL;
        return image;
}

/* HFlip */

IMAGE *HFlip(IMAGE *image)
{
        assert(image);
        int             x, y;
        unsigned char   r, g, b;

        for (y = 0; y < image->Height; y ++) {
                for (x = 0; x < image->Width / 2; x ++) {
                        r = GetPixelR(image, image->Width - 1 - x, y);
                        g = GetPixelG(image, image->Width - 1 - x, y);
                        b = GetPixelB(image, image->Width - 1 - x, y);

                        SetPixelR(image, image->Width - 1 - x, y, GetPixelR(image, x, y));
                        SetPixelG(image, image->Width - 1 - x, y, GetPixelG(image, x, y));
                        SetPixelB(image, image->Width - 1 - x, y, GetPixelB(image, x, y));
                        
                        SetPixelR(image, x, y, r);
                        SetPixelG(image, x, y, g);
                        SetPixelB(image, x, y, b);
                }
        }
        return image;
}


/* VMirror */


IMAGE *Vmirror(IMAGE *image)
{
        assert(image);
        int x, y;

        for (y = 0; y < image->Height / 2; y ++) {
                for (x = 0; x < image->Width; x ++) {
                        SetPixelR(image, x, image->Height - 1 - y, GetPixelR(image, x, y));
                        SetPixelG(image, x, image->Height - 1 - y, GetPixelG(image, x, y));
                        SetPixelB(image, x, image->Height - 1 - y, GetPixelB(image, x, y));
                }
        }
        return image;
}


/* Zoom */

IMAGE *Zoom(IMAGE *image)
{
        assert(image);
        int x, y;
        const int X_OFFSET = image->Width / 4;
        const int Y_OFFSET = image->Height / 4;
        IMAGE *imagetmp = NULL;

        imagetmp = CreateImage(image->Width, image->Height);
        assert(imagetmp);

        for (y = 0; y < image->Height; y++) {
                for (x = 0; x < image->Width; x++) {
                        SetPixelR(imagetmp, x, y, GetPixelR(image, x, y));
                        SetPixelG(imagetmp, x, y, GetPixelG(image, x, y));
                        SetPixelB(imagetmp, x, y, GetPixelB(image, x, y));
                }
        }

        for (y = 0; y < image->Height; y++) {
                for (x = 0; x < image->Width; x++) {
                        SetPixelR(image, x, y, GetPixelR(imagetmp, x / ZOOM_FACTOR + X_OFFSET, y / ZOOM_FACTOR + Y_OFFSET));
                        SetPixelG(image, x, y, GetPixelG(imagetmp, x / ZOOM_FACTOR + X_OFFSET, y / ZOOM_FACTOR + Y_OFFSET));
                        SetPixelB(image, x, y, GetPixelB(imagetmp, x / ZOOM_FACTOR + X_OFFSET, y / ZOOM_FACTOR + Y_OFFSET));
                }
        }
        DeleteImage(imagetmp);
        imagetmp = NULL;
        return image;

}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
                                                                                                                                                     
