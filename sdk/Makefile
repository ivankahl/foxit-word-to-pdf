CXX=g++
# Foxit PDF SDK lib and head files include
INCLUDE_PATH=-Iinclude
LIBNAME=./lib/libfsdk_linux64.so
LDFLAGS=-Wl,-rpath,../../lib
# Specify output options
DEST_PATH=./bin/rel_gcc
OBJ_PATH=./obj/rel
# Flags for compiling the application
CCFLAGS=-c
CXXFLAGS=-std=c++11
DEST=-o $(DEST_PATH)/$@
OBJ_DEST= -o $(OBJ_PATH)/$@
# Specify different tasks
all: convert
dir:
	mkdir -p $(DEST_PATH)
	mkdir -p $(OBJ_PATH)
convert.o: convert.cpp
	$(CXX) $(CCFLAGS) $(CXXFLAGS) $(INCLUDE_PATH) $^ $(OBJ_DEST)
convert: convert.o
	$(CXX) $(OBJ_PATH)/convert.o $(DEST) $(LDFLAGS) $(LIBNAME)