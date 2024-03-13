FILES = bin/Cahn-Hilliard
CXX = g++
CFLAGS = -Wall -Wextra -std=c++11 -I/include -I./include
SRC = src/main.cpp src/setup.cpp
INC = include/Cahn-Hilliard.hpp

all: 
	$(CXX) $(CFLAGS) -o $(FILES) $(SRC)

clean:
	rm -f $(FILES)


