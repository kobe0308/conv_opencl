#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bmp.h"
#include "convolution.h"

int main(int argc, char *argv[])
{
	printf("convolution using opencl!!\n");
	BMP bmp;
    bmpLoad(&bmp, argv[1]);
    bmpPrint(&bmp);
//    bmpSetBox(&bmp, 0, 0, 20, 20, 0x66, 0x33, 0x99);
	convolution(&bmp,NULL,NULL,0,cpu);
    bmpSave(&bmp, argv[2]);
    return 0;

}


