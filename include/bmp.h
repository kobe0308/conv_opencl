#ifndef __BMP_H__
#define __BMP_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef long UINT32;
typedef unsigned short int UINT16;
typedef unsigned char BYTE;

#define IMAGE_FILE_PATH "/home/kobeyu/workspace/opencl/convoulution/conv_opencl/res/lena.bmp"
#define HEADER_SIZE 14
#define INFO_SIZE 40
#define DataSize(bmp) (bmp->width*bmp->height*3)

typedef struct BMP {
    BYTE header[HEADER_SIZE];    
    BYTE info[INFO_SIZE];
    // Header
    UINT16 signature; // Magic Number = "BM" = 0x4D42
    UINT32 fileSize; // File size in bytes
    UINT32 hreserved; // unused (=0)
    UINT32 dataOffset; // File offset to Raster Data
    // InfoHeader
    UINT32 size; // Size of InfoHeader =40 
    UINT32 width; // Bitmap Width
    UINT16 height; // Bitmap Height
    UINT16 planes; // Number of Planes (=1)
    UINT16 bitsPerPixel; // Bits per Pixel, 1, 4, 8, 16, 24
    UINT32 compression; // Type of Compression, 0 = BI_RGB no compression, 1 = BI_RLE8 8bit RLE encoding, 2 = BI_RLE4 4bit RLE encoding
    UINT32 imageSize; // (compressed) Size of Image, It is valid to set this =0 if Compression = 0
    UINT32 xPixelsPerM; // horizontal resolution: Pixels/meter
    UINT32 yPixelsPerM; // vertical resolution: Pixels/meter
    UINT32 colorsUsed; // Number of actually used colors
    UINT32 colorsImportant; // Number of important colors , 0 = all
    // ColorTable : present only if Info.BitsPerPixel <= 8 colors should be ordered by importance
    BYTE blue; // Blue intensity
    BYTE green; // Green intensity
    BYTE red; // Red intensity
    BYTE creserved; // unused (=0)
    // Raster Data
    BYTE *data;
} BMP;

typedef struct Pixel {
    BYTE R;
    BYTE G;
    BYTE B;
} Pixel;

typedef struct Pixel_Gray {
	BYTE Value
} Pixel_Gray;

#define U16(x)    ((unsigned short) (x))
#define U32(x)    ((int) (x))
#define B2U16(bytes,offset)  (U16(bytes[offset]) | U16(bytes[offset+1]) << 8)
#define B2U32(bytes,offset)  (U32(bytes[offset]) | U32(bytes[offset+1]) << 8 | \
                   U32(bytes[offset+2]) << 16 | U32(bytes[offset+3]) << 24)

int bmpLoad(BMP *bmp, char *fileName);
int bmpSave(BMP *bmp, char *fileName);
int bmpPrint(BMP *bmp);
int bmpSetPixel(BMP *bmp, int x, int y, BYTE R, BYTE G, BYTE B);
int bmpSetBox(BMP *bmp, int x, int y, int w, int h, BYTE R, BYTE G, BYTE B);




#endif
