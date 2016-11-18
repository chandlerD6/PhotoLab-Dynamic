# Makefile: PhotoLab2

all: PhotoLab PhotoLabTest

clean:
        rm -f FileIO.o
        rm -f DIPs.o
        rm -f Advanced.o
        rm -f PhotoLab.o
        rm -f PhotoLab
        rm -f libfileIO.a
        rm -f libfilter.a
        rm -f PhotoLabTest.o
        rm -f PhotoLabTest
        rm -f FileIODEBUG.o
        rm -f libfileIODEBUG.a
        rm -f Test.o
        rm -f TestDEBUG.o
        rm -f Image.o
        rm -f negative.ppm
        rm -f colorfilter.ppm
        rm -f edge.ppm
        rm -f hflip.ppm
        rm -f vmirror.ppm
        rm -f zoom.ppm
        rm -f noise.ppm
        rm -f shuffle.ppm
        rm -f posterize.ppm
        rm -f overlay.ppm
        rm -f crop.ppm
        rm -f smallresize.ppm
        rm -f bigresize.ppm
        rm -f circle.ppm
        rm -f rotate.ppm

PhotoLab: libfileIO.a libfilter.a PhotoLab.o
        gcc PhotoLab.o -L. -lm -lfileIO -lfilter -o PhotoLab

PhotoLabTest: libfileIODEBUG.a libfilter.a PhotoLabTest.o
        gcc -g -DDEBUG PhotoLabTest.o -L. -lm  -lfileIODEBUG -lfilter -o PhotoLabTest

FileIODEBUG.o: FileIO.c FileIO.h Constants.h Image.h
        gcc -c -g -DDEBUG FileIO.c -o FileIODEBUG.o -ansi -Wall

FileIO.o: FileIO.c FileIO.h Constants.h Image.h
        gcc -c FileIO.c -o FileIO.o -ansi -Wall

DIPs.o: DIPs.c DIPs.h Constants.h
        gcc -c DIPs.c -o DIPs.o -ansi -Wall

Image.o: Image.c Image.h Constants.h
        gcc -c Image.c -o Image.o -ansi -Wall

Advanced.o: Advanced.c Advanced.h Constants.h FileIO.h
        gcc -c Advanced.c -o Advanced.o -ansi -Wall

TestDEBUG.o: Test.c Test.h Constants.h Advanced.h DIPs.h FileIO.h Image.h
        gcc -c -g -DDEBUG Test.c -o TestDEBUG.o -ansi -Wall

Test.o: Test.c Test.h Constants.h Advanced.h DIPs.h FileIO.h Image.h
        gcc -c Test.c -o Test.o -ansi -Wall

PhotoLab.o: PhotoLab.c Advanced.h Constants.h DIPs.h FileIO.h
        gcc -c PhotoLab.c -o PhotoLab.o -ansi -Wall

PhotoLabTest.o: PhotoLab.c Advanced.h Constants.h DIPs.h FileIO.h
        gcc -c -g -DDEBUG PhotoLab.c -o PhotoLabTest.o -ansi -Wall

libfileIODEBUG.a: FileIODEBUG.o TestDEBUG.o
        ar rc libfileIODEBUG.a FileIODEBUG.o TestDEBUG.o
        ranlib libfileIODEBUG.a

libfileIO.a: FileIO.o Test.o
        ar rc libfileIO.a FileIO.o Test.o
        ranlib libfileIO.a

libfilter.a: DIPs.o Advanced.o Image.o
        ar rc libfilter.a DIPs.o Advanced.o Image.o
        ranlib libfilter.a
