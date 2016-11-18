#include <stdio.h>
#include <string.h>

#include "Test.h"
#include "Image.h"
#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{
        int FileNotRead ;

#ifdef DEBUG
        AutoTest();
        FileNotRead = 0 ;
#else

        char fname[SLEN];
        int choice;

        int target_r;
        int target_g;
        int target_b;
        int threshold;
        double factor_r;
        double factor_g;
        double factor_b;
        int FileNotSaved;
        IMAGE *image = NULL;
        IMAGE *overlayImage = NULL;

        FileNotRead = 1 ;
        FileNotSaved = 0;
        PrintMenu();
        printf("please make your choice: ");
        scanf("%d", &choice);
        while (choice != 18) {
                switch (choice) {
                case 1:
                        if (image != NULL){
                                DeleteImage(image);
                        }
                        printf("Please input the file name to load: ");
                        scanf("%s", fname);
                        image = LoadImage(fname);
                        if(image != NULL){
                                FileNotRead = 0;
                        }
                        break;
                case 2:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                printf("Please input the file name to save: ");
                                scanf("%s", fname);
                                FileNotSaved = SaveImage(fname, image);
                                if (FileNotSaved != 0){
                                        printf("The image failed to be saved!!\n");
                                }
                        }
                        break;
                case 3:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                Negative(image);
                                printf( "\"Negative\" operation is done!\n" );
                        }
                        break;
                case 4:
                        if (FileNotRead != 0)
                        {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                printf("Enter Red   component for the target color: ") ;
                                scanf("%d", &target_r) ;
                                printf("Enter Green component for the target color: ") ;
                                scanf("%d", &target_g) ;
                                printf("Enter Blue  component for the target color: ") ;
                                scanf("%d", &target_b) ;
                                printf("Enter threshold for the color difference: ") ;
                                scanf("%d", &threshold) ;
                                printf("Enter value for Red component in the target color: ") ;
                                scanf("%lf", &factor_r) ;
                                printf("Enter value for Green component in the target color: ") ;
                                scanf("%lf", &factor_g) ;
                                printf("Enter value for Blue  component in the target color: ") ;
                                scanf("%lf", &factor_b) ;

                                ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                                printf("\"Color Filter\" operation is done!\n");
                        }
                        break;
                case 5:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                Edge(image);
                                printf("\"Edge\" operation is done!\n");
                        }
                        break;
                case 6:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                HFlip(image);
                                printf( "\"Horizontally Flip\" operation is done!\n" );
                        }
                        break;
                case 7:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                Vmirror(image);
                                printf("\"Vertically Mirror\" operation is done!\n");
                        }
                        break;
                case 8:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                Zoom(image);
                                printf("\"Zoom\" operation is done!\n");
                        }
                        break;
                case 9:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                int n;
                                printf("Please input noise percentage: ");
                                scanf("%d", &n);
                                AddNoise(image, n);
                                printf("\"Noise\" operation is done!\n");
                        }
                        break;
                case 10:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                Shuffle(image);
                                printf("\"Shuffle\" operation is done!\n");
                        }
                        break;
                case 11:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n") ;
                        } else {
                                unsigned char rbits, gbits, bbits;
                                printf("Enter the number of posterization bits for R chennel (1 to 8):");
                                scanf("%hhu", &rbits);
                                printf("Enter the number of posterization bits for G chennel (1 to 8):");
                                scanf("%hhu", &gbits);
                                printf("Enter the number of posterization bits for B chennel (1 to 8):");
                                scanf("%hhu", &bbits);
                                Posterize(image, rbits, gbits, bbits);
                                printf("\"Posterize\" operation is done!\n");
                        }
                        break;
                case 12:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n");
                        } else {
                                int x_offset, y_offset;
                                unsigned char backgroundR, backgroundG, backgroundB;
                                printf("Please input X coordinate of the overlay image: ");
                                scanf("%d" , &x_offset);
                                printf("Please input Y coordinate of the overlay image: ");
                                scanf("%d" , &y_offset);
                                printf("Please input background R: ");
                                scanf("%c" , &backgroundR);
                                printf("Please input background G: ");
                                scanf("%c" , &backgroundG);
                                printf("Please input background B: ");
                                scanf("%c" , &backgroundB);
                                overlayImage = LoadImage("balloon");
                                Overlay(image, overlayImage, x_offset, y_offset, backgroundR, backgroundG, backgroundB);
                                printf("\"Overlay\" operation is done!\n");
                        }
                        break;
                case 13:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n");
                        } else {
                                int degree;
                                printf("Please input the rotate degree (90, 180 or 270): ");
                                scanf("%d" , &degree);
                                Rotate(image, degree);
                                printf("\"Rotate\" operation is done!\n");
                        }
                        break;
                case 14:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n");
                        } else {
                                int x_offset, y_offset, width, height;
                                printf("Please enter the X offset value: ");
                                scanf("%d" , &x_offset);
                                printf("Please enter the Y offset value: ");
                                scanf("%d" , &y_offset);
                                printf("Please input the crop width: ");
                                scanf("%d" , &width);
                                printf("Please input the crop height: ");
                                scanf("%d" , &height);
                                Crop(image, x_offset, y_offset, width, height);
                                printf("\"Crop\" operation is done!\n");
                        }
                        break;
                case 15:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n");
                        } else {
                                int percentage;
                                printf("Please input the resizing percentage (integer between 1-500): ");
                                scanf("%d" , &percentage);
                                Resize(image, percentage);
                                printf("\"Resizing the image\" operation is done!\n");
                        }
                        break;
                case 16:
                        if (FileNotRead != 0) {
                                printf("No Image Read Yet !!\n");
                        } else {

                                int x_offset, y_offset, outerRadius, borderWidth;
                                printf("Please enter the X offset value: ");
                                scanf("%d" , &x_offset);
                                printf("Please enter the Y offset value: ");
                                scanf("%d" , &y_offset);
                                printf("Please input the outer radius: ");
                                scanf("%d" , &outerRadius);
                                printf("Please input the border width: ");
                                scanf("%d" , &borderWidth);
                                MetalCircle(image, x_offset, y_offset, outerRadius, borderWidth);
                                printf("\"MetalCircle\" operation is done!\n");
                        }
                        break;
                case 17:
                        AutoTest();
                        FileNotRead = 0 ;
                        break;
                default:
                        printf("Invalid selection!\n");
                        break;
                }

                PrintMenu();
                printf("please make your choice: ");
                scanf("%d", &choice);
        }
        if(image != NULL){
                DeleteImage(image);
        }
#endif
        return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void
PrintMenu()
{
        printf("\n--------------------------------\n");
        printf(" 1:  Load a PPM image\n");
        printf(" 2:  Save an image in PPM and JPEG format\n");
        printf(" 3:  Make a negative of an image\n");
        printf(" 4:  Color filter an image\n");
        printf(" 5:  Sketch the edge of an image\n");
        printf(" 6:  Flip an image horizontally\n");
        printf(" 7:  Mirror an image vertically\n");
        printf(" 8:  Zoom an image\n");
        printf(" 9:  Add noise to an image\n");
        printf("10:  Shuffle an image\n");
        printf("11:  Posterize an image\n");
        printf("12:  Overlay\n");
        printf("13:  Rotate clockwise\n");
        printf("14:  Crop\n");
        printf("15:  Resize\n");
        printf("16:  MetalCircle\n");
        printf("17:  Test all functions\n");
        printf("18:  Exit\n");
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
                                                                                                                           

