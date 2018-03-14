#include "convolution.h"

int cpu_convolution(BMP *bmp, BMP *out, int kernel[], size_t kernelsz)
{
	//check parameter
	printf("kernel size:%d\n",kernelsz);
	assert(1==(kernelsz%2));
	int half_kersz = sqrt(kernelsz)/2;
	int i,j,ker_i,ker_j,idx,ker_idx;
	Pixel *pixel,*pixel_out;
	Pixel_Gray *pixel_gray, *pixel_grayout;
	float w = 0.5; 
	int sum_r, sum_g, sum_b;
	int ker_val;


	for (i=1; i<bmp->height-1; i++)
	{
		for (j=1; j<bmp->width-1; j++)
		{	
			sum_r = 0;
			sum_g = 0;
			sum_b = 0;
			ker_idx = 0;
			for(ker_i = -1*half_kersz;ker_i<=((half_kersz));ker_i++) {
				for(ker_j = -1*half_kersz;ker_j<=((half_kersz));ker_j++) {
						
					idx = (i+ker_i)*bmp->width+(j+ker_j);
					switch (bmp->bitsPerPixel) {
						case 8:
							pixel_gray = (Pixel_Gray*)&bmp->data[idx*sizeof(Pixel_Gray)];
							ker_val = kernel[ker_idx];
							sum_g += ker_val * pixel_gray->Value;
							break;
						case 24:
							pixel = (Pixel*)&bmp->data[idx*sizeof(Pixel)];
							ker_val = kernel[ker_idx];
							sum_r += ker_val * pixel->R;
							sum_g += ker_val * pixel->G; 
							sum_b += ker_val * pixel->B;
							break;
						default:
							printf("not support format!\n");
							exit(0);
						break;
					}
					
					ker_idx++;
				}		
			}
			//write back
			
			idx = (i)*out->width+(j);
			switch (bmp->bitsPerPixel) {
				case 8:
					pixel_gray = (Pixel_Gray*)&out->data[idx*sizeof(Pixel_Gray)];
					pixel_gray->Value = sum_g/kernelsz; 
					break;
				case 24:
					
					pixel = (Pixel*)&out->data[idx*sizeof(Pixel)];
					pixel->R = sum_r/kernelsz;
					pixel->G = sum_g/kernelsz;
					pixel->B = sum_b/kernelsz;
					break;
				default:
					printf("not support format!\n");
					exit(0);
					break;
			}

			//loop unrolling
			
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


