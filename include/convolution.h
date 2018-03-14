#ifndef __CONVOLUTION_H__
#define __CONVOLUTION_H__


#include <stdio.h>
#include <math.h>
#include "bmp.h"

typedef enum{
	cpu=0,
	opencl,
	arm_neon,
	nvidia_cuda,
	x86_avx 
}op_target;


int convolution(BMP *bmp, BMP *out, void *kernel, size_t kernelsz, op_target target);



#endif
