#OBJS specifies which files to compile as part of the project
OBJS = src/main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS =-w

CXXFLAGS=-g -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS =

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = todo

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)