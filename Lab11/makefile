# Config, just variables
CC=gcc
CFLAGS=-Wall -g 
LFLAGS=-lm 
TARGET1=out3
TARGET2=out5
 
# Generate source and object lists, also just string variables
#CRSC1 for 3x3
C_SRCS1 := driver3x3.c src/functions.c
#CRSC2 for 5x5
C_SRCS2 := driver5x5.c src/functions.c
HDRS := src/functions.h
OBJS := bin/functions.o bin/driver3x3.o bin/driver5x5.o

# default: tells user how they can use makefile
all:
	@echo -e "\nType:\nmake run3: Run with 3x3 filter\nmake run5: Run with 5x5 filter"
 
# Link all built objects 
build1: $(OBJS) 
	$(CC) $(C_SRCS1) -o $(TARGET1) $(LFLAGS)

build2: $(OBJS) 
	$(CC) $(C_SRCS2) -o $(TARGET2) $(LFLAGS)

# special build rule to put obj files into bin
bin/%.o: %.c $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bin/%.o: src/%.c $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#compiles and runs 3x3 filter on ppm image
run3: build1
	./$(TARGET1) mario.ppm

#compiles and runs 5x5 filter on ppm image
run5: build2
	./$(TARGET2) mario.ppm

#tars all contents
tar: 
	tar -czf nmowll_Lab11.tar.gz *