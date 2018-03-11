
PROJ_ROOT	:= $(shell pwd)

INCLUDES 	:= -I"$(PROJ_ROOT)/include"

CFLAGS		:= -o0 -Wall -g
LDFLAGS		:= -lOpenCL
CC			:= gcc

all: convolution

convolution: src/main.c
	$(CC) src/main.c $(INCLUDES) $(CFLAGS) $(LDFLAGS) -o bin/conv_opencl

run: convolution
	./bin/conv_opencl
clean:
	rm -f $(PROJ_ROOT)/bin/conv_opencl

