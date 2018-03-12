#include "convolution.h"

int cpu_convolution(BMP *bmp, BMP *out, void *kernel, size_t kernelsz)
{
	int i,j,idx;
	Pixel *pixel;
	float w = 0.5;
	for (i=0; i<bmp->height; i++)
	{
		for (j=0; j<bmp->width; j++)
		{
			idx = i*bmp->width+j;
			pixel = (Pixel*)&bmp->data[idx*sizeof(Pixel)];
			pixel->R *= w;
			pixel->G *= w;
			pixel->B *= w;
		}
	}

	return 0;
}

int opencl_convolution(BMP *bmp, void *kernel, size_t kernelsz)
{
	return 0;
}



int convolution(BMP *bmp, BMP *out, void *kernel, size_t kernelsz, op_target target) 
{
	switch(target)
	{
		case cpu:
			cpu_convolution(bmp,out,kernel,kernelsz);
		case opencl:
			opencl_convolution(bmp,kernel,kernelsz);
		default:
			break; 
	}


	return 0;
}


