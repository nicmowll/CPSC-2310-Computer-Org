#Configurations, these are just variables to let the makefile know which compiler, flags and libraries to use
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
TARGET=out

#Locates the source files without explicitly naming them in the current and subdirectories
C_SRCS := \
  $(wildcard *.c) \
  $(wildcard src/*.c) \
  $(wildcard src/**/*.c)
#Locates the header files without explicitly naming them in the current and subdirectories
HDRS := \
  $(wildcard *.h) \
  $(wildcard src/*.h) \
	$(wildcard src/**/*.h)
#Takes list of src files and generates the .o files
OBJS := $(patsubst %.c, bin/%.o, $(wildcard *.c))
OBJS += $(filter %.o, $(patsubst src/%.c, bin/%.o, $(C_SRCS)))

#Calls the build target and afterward lets us know it's all done in console
all: build
	@echo "All Done"

#Links all of the build objects in compiler command
build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

#Creates a new bin directory and stores the .o files there so they don't clutter the current dir
#This bin command selects the src files in the current directory
bin/%.o: %.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#Creates a new bin directory and stores the .o files there so they don't clutter the current dir
#This bin command selects the src files in the src directory
bin/%.o: src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


#Cleans up the excess files created from builds so it is nicer
clean:
	rm -f $(TARGET)
	rm -rf bin
#Runs the program with the command line arguments already in place to make it easier
run: build
	./$(TARGET)
#Displays that the makefile locates the sources and header files in the console
which:
	@echo "FOUND SOURCES: ${C_SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"
	@echo "TARGET OBJS: ${OBJS}"

tar: 
	tar -czf nmowll_Lab10.tar.gz *