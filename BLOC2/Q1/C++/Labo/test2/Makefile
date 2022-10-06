CC = g++
CFLAGS = -g -Wall -W -D DEBUG -O3

SRC_DIR := ../Source
OBJ_DIR := ../Source

CPP_SOURCES := $(wildcard *.cpp $(SRC_DIR)/*.cpp)
CPP_OBJECTS := $(CPP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
CPP_HEADERS = ../Include/$(wildcard *.h)

all: test2a test2b test2c

test2a: $(filter-out Test2b.cpp Test2c.cpp, $(CPP_OBJECTS)) 
	$(CC) $(CFLAGS) -I $(CPP_HEADERS) -o $@ $(filter-out Test2b.cpp Test2c.cpp, $(CPP_OBJECTS))

test2b : $(filter-out Test2a.cpp Test2c.cpp, $(CPP_OBJECTS)) 
	$(CC) $(CFLAGS) -I $(CPP_HEADERS) -o $@ $(filter-out Test2a.cpp Test2c.cpp, $(CPP_OBJECTS))

test2c : $(filter-out Test2a.cpp Test2b.cpp, $(CPP_OBJECTS)) 
	$(CC) $(CFLAGS) -I $(CPP_HEADERS) -o $@ $(filter-out Test2a.cpp Test2b.cpp, $(CPP_OBJECTS))

%.o: %.cpp
	$(CC) $(CFLAGS) -c -I $(CPP_HEADERS) $< -o $@

clean:
	rm -rf ../Source/*.o
	rm -rf test2a test2b test2c
