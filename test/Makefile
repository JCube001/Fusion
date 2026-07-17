CXX = g++

CPPFLAGS = -I. -I.. -MMD
CXXFLAGS = -Wall -Wextra -O2
LDLIBS =

CXXFLAGS += $(shell pkg-config --cflags catch2-with-main)
LDLIBS += $(shell pkg-config --libs catch2-with-main)

TARGET = tests
SRCS = $(wildcard ../*.cpp *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

# Compiler-generated dependency rules
# THIS MUST BE THE LAST LINE IN THE MAKEFILE
-include $(DEPS)
