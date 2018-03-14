PROJ_ROOT	:= $(shell pwd)

INCLUDES 	:= -I"$(PROJ_ROOT)/include"

CFLAGS		:= -o0 -Wall -g
LDFLAGS		:= -lOpenCL -lm
CC			:= gcc

all: main bmp convolution
	$(CC) -o bin/conv_opencl bin/bmp.o bin/main.o bin/convolution.o $(LDFLAGS)

bmp: src/bmp.c 
	$(CC) -c src/bmp.c $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o bin/bmp.o

convolution:
	$(CC) -c src/convolution.c $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o bin/convolution.o

main: src/main.c
	$(CC) -c src/main.c $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o bin/main.o

run: all
	./bin/conv_opencl res/lena.bmp res/lena_out.bmp

clean:
	rm -f $(PROJ_ROOT)/bin/conv_opencl
	rm -f $(PROJ_ROOT)/bin/*.o

