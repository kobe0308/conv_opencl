#include <stdio.h>
#include "def.h"

int main()
{
	printf("convolution using opencl!!\n");
	loadBMPFile(IMAGE_FILE_PATH);

}


void *loadBMPFile(char *fileName)
{
	BITMAPINFOHEADER bmpHeader;
	printf("prepare load file:%s\n",fileName);
	FILE *imgFile; 
	imgFile = fopen(fileName,"rb+");

	if(imgFile != NULL)
		printf("open img file successful!\n");

	fseek(imgFile,2,SEEK_SET);
	fread(&bmpHeader.size,4,1,imgFile);
	printf("Size=%d\n",bmpHeader.size);

	fseek(imgFile,18,SEEK_SET);
	fread(&bmpHeader.width,4,1,imgFile);







	fclose(imgFile);


	return NULL;

}

