FILES = bin/cahn-hilliard
CXX = g++
CFLAGS = -Wall -Wextra -std=c++11 -I/include -I./include
SRC = src/main.cpp src/setup.cpp
INC = include/cahn-hilliard.hpp

all: 
	$(CXX) $(CFLAGS) -o $(FILES) $(SRC)

clean:
	rm -f bin/* 


