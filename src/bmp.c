#include "bmp.h"

int bmpLoad(BMP *bmp, char *fileName) {
   FILE *file;
   BYTE header[14];
   BYTE info[40];

   if ((file = fopen(fileName, "rb") ) == NULL ) {
      fprintf(stderr, "Error: bmpLoad(), File open fail!\n");
      exit(0);
   }

   fread(header, 1, HEADER_SIZE, file);
   fread(info, 1, INFO_SIZE, file);
   memcpy(bmp->header, header, HEADER_SIZE);
   memcpy(bmp->info, info, INFO_SIZE);
   // Header
   bmp->signature = B2U16(header,0); assert(bmp->signature == 0x4D42);
   bmp->fileSize = B2U32(header,2);
   bmp->dataOffset = B2U32(header,10);
   // InfoHeader
   bmp->size = B2U32(info,0); assert(bmp->size==40);
   bmp->width = B2U32(info,4);
   bmp->height = B2U32(info,8);
   bmp->planes = B2U16(info,12); assert(bmp->planes==1);
   bmp->bitsPerPixel = B2U16(info,14); assert(bmp->bitsPerPixel==24);
   bmp->compression = B2U32(info,16);
   bmp->imageSize = B2U32(info,20);
   bmp->xPixelsPerM = B2U32(info,24);
   bmp->yPixelsPerM = B2U32(info,28);
   bmp->colorsUsed = B2U32(info,32);
   bmp->colorsImportant = B2U32(info,36);

   bmp->data = malloc(DataSize(bmp));
   fseek(file, bmp->dataOffset, SEEK_SET);
   fread(bmp->data, 1, DataSize(bmp), file);

   fclose (file);
   return 0;
}

int bmpPrint(BMP *bmp) {
   printf("==== Header ====\n");
   printf("Signature = %04X\n", bmp->signature); // 0x4d42 = BM
   printf("FileSize = %ld \n", bmp->fileSize);
   printf("DataOffset = %ld \n", bmp->dataOffset);
   printf("==== Info ======\n");
   printf("size = %ld \n", bmp->size);
   printf("Width = %ld \n", bmp->width);
   printf("Height = %d \n", bmp->height);
   printf("Planes = %d \n", bmp->planes);
   printf("BitsPerPixel = %d \n", bmp->bitsPerPixel);
   printf("Compression = %ld \n", bmp->compression);
   printf("ImageSize = %ld \n", bmp->imageSize);
   printf("XpixelsPerM = %ld \n", bmp->xPixelsPerM);
   printf("YpixelsPerM = %ld \n", bmp->yPixelsPerM);
   printf("ColorsUsed = %ld \n", bmp->colorsUsed);
   printf("ColorsImportant = %ld \n", bmp->colorsImportant);

   return 0;
}

int bmpSetPixel(BMP *bmp, int x, int y, BYTE R, BYTE G, BYTE B) {
    Pixel *pixel;
    int idx = y * bmp->width + x;
    pixel = (Pixel*) &bmp->data[idx * sizeof(Pixel)];
    pixel->R = R;
    pixel->G = G;
    pixel->B = B;
	return 0;
}

int bmpSetBox(BMP *bmp, int x, int y, int w, int h, BYTE R, BYTE G, BYTE B) {
    int i,j;
    for (i=0; i< 0+w; i++)
        for (j=0; j<h; j++)
            bmpSetPixel(bmp, x+i, y+j, R, G, B);

	return 0;
}

int bmpSave(BMP *bmp, char *fileName) {
    FILE *file;
    if ((file = fopen(fileName, "wb") ) == NULL ) {
        fprintf(stderr, "Error: bmpSave(), File create fail!\n");
        exit(0);
    }
    fwrite(bmp->header, 1, HEADER_SIZE, file);
    fwrite(bmp->info, 1, INFO_SIZE, file);
    fseek(file, bmp->dataOffset, SEEK_SET);
    fwrite(bmp->data, 1, DataSize(bmp), file);
    fclose(file);
	return 0;


}

