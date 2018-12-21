CC= g++
CFLAGS= -std=c++11 -Wall -g #-O2 # -D NDEBUG -O3


# Library files
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp,build/%.o,$(SRCS))

# Executable files
MAINS=$(wildcard main/*.cpp)
EXES=$(patsubst main/%.cpp,bin/%,$(MAINS))


# Files that shouldn't be deleted
.PRECIOUS: %/  build/%.o


# Default target
all: exe

# run: exe
# 	@ ./bin/$(EXECUTAVEL) #divulga.csv

clean:
	rm -f -r ./.dep
	rm -f -r ./build
	rm -f -r ./bin


# Create a directory
%/:
	mkdir -p $@

# Compile all executables
exe: $(EXES)


# Compile libraries from src/ to build/
build/%.o: src/%.cpp | build/  $(dir .dep/src/%)/
	$(CC) -o $@  -c  $<  $(CFLAGS)

	@ $(CC) -MM -MT "$@"  $< $(CFLAGS)  > .dep/$<.d

# Compile from main/ to bin/
bin/%: main/%.cpp $(OBJS) | bin/  $(dir .dep/main/%)/
	$(CC) -o $@  -I "./src/"  $< $(OBJS)  $(CFLAGS)
	
	@ $(CC) -I "./src/" -MM -MT "$@"  $< $(CFLAGS)  > .dep/$<.d


# Include list of dependencies
include $(wildcard .dep/**/*)
