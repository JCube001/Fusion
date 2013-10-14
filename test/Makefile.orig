#### Project ####
PROJECT = fusion-test

# Directories
BINDIR  = bin
SRCDIR  = ./ ../ ../utility
OBJDIR  = $(BINDIR)/obj

# Target
TARGET  = $(BINDIR)/$(PROJECT)

#### Compiler ####
CC      = g++
CFLAGS  = -O0 -Wall -ggdb -std=c++11 -D_FUSION_TEST
LIBS    = -lm

#### Source ####
SRC     := $(foreach DIR,$(SRCDIR),$(wildcard $(DIR)/*.cpp))
INC     := $(foreach DIR,$(SRCDIR),-I$(DIR))
OBJ     := $(addprefix $(OBJDIR)/,$(notdir $(SRC:.cpp=.o)))

CFLAGS  += $(INC)

VPATH   = $(SRCDIR)

#### Rules ####
.PHONY: all clean

all: $(BINDIR) $(TARGET)

$(BINDIR) $(OBJDIR):
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

$(OBJ): $(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BINDIR)

