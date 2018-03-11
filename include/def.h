

#define IMAGE_FILE_PATH "/home/kobeyu/workspace/opencl/convoulution/conv_opencl/res/lena.bmp"

typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int planes;
	unsigned short bitcount;
	unsigned int size
} BITMAPINFOHEADER;

typedef struct {
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Pixel;

void *loadBMPFile(char *fileName);


