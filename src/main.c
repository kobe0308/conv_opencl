#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include "bmp.h"
#include "convolution.h"

int main(int argc, char *argv[])
{
	printf("convolution start...\n");
	BMP bmp,gx,out;
    bmpLoad(&bmp, argv[1]);
    bmpLoad(&gx, argv[1]);
    bmpLoad(&out, argv[1]);
    bmpPrint(&bmp);
//    bmpSetBox(&bmp, 0, 0, 20, 20, 0x66, 0x33, 0x99);
	
//sobl Gx
	int kernel_Gx[] = {-1,0,1,-2,0,2,-1,0,1};
	int kernel_Gy[] = {1,2,1,0,0,0,-1,-2,-1};

	convolution(&bmp,&gx,kernel_Gx,sizeof(kernel_Gx)/sizeof(int),cpu);
	convolution(&gx,&out,kernel_Gy,sizeof(kernel_Gy)/sizeof(int),cpu);
    bmpSave(&out, argv[2]);
    return 0;

}


