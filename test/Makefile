# Makefile for building a test suite which tests the entire Fusion library

# Project name
PROJECT = fusion-test

# Google Test library
LIBGTEST = lib/libgtest.a

# C++ compiler
CXX = g++

# Remove file program
RM = rm -f

# C preprocessor flags
CPPFLAGS += -Iinclude -I..

# C++ compiler flags
CXXFLAGS += -g -Wall -Wextra -std=c++11

# Linker flags
# Note that pthread is required by Google Test
LDFLAGS += -L$(LIBGTEST) -lpthread -lm

# Source files
SRC = $(wildcard ../*.cpp) $(wildcard src/*.cpp)

# Object files
OBJ = $(patsubst %.cpp,%.o,$(SRC))

#
# Rules
#

.PHONY: all clean dist-clean

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

dist-clean: clean
	$(RM) $(PROJECT)

