CC = g++
CFLAGS = -g -Wall -W

SRC_DIR := ../Source
OBJ_DIR := ../Source

CPP_SOURCES := $(wildcard *.cpp $(SRC_DIR)/*.cpp)
CPP_OBJECTS := $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
CPP_HEADERS = ../Include/$(wildcard *.h)
prog: $(CPP_OBJECTS) 
	$(CC) $(CFLAGS) -I $(CPP_HEADERS) -o $@ $(CPP_OBJECTS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -I $(CPP_HEADERS) $< -o $@

clean:
	rm -rf ../Source/*.o
	rm -rf prog
