FILES = bin/Cahn-Hilliard
CXX = g++
CFLAGS = -Wall -Wextra -std=c++11 -I/include -I./include
# FLIB = $(framework)/lib/libframework.a
SRC = src/main.cpp
INC = include/Cahn-Hilliard.hpp

all: 
	$(CXX) $(CFLAGS) -o $(FILES) $(SRC)

clean:
	rm -f $(FILES)


