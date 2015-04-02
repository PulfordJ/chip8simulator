# Takes the name of the current directory as a the executable and "pr" name
TARGET  := $(shell basename $$PWD | tr '[:upper:]' '[:lower:]')
# Compiler
CC      := g++
AR		:= ar
# Warning levels
WARN    :=
# Optimisation
OFLAGS  := 
# Link Options
LDFLAGS := 
# Link Libraries
LDLIBS 	:= 

# Source directory
SRCDIR	:= src
# Include directory
INCDIR	:= include
# Object directory
OBJDIR	:= obj

CFLAGS	:= -I $(INCDIR)

# setting the vpath (additionnal search path for make)
VPATH	:= $(INCDIR) $(SRCDIR) $(OBJDIR)

CPP_SRCS    = $(wildcard src/*.cpp)
OBJ_FILES   = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPP_SRCS))

GTEST_DIR	= test/googletest
TEST_DIR	= test

all: objdir ${TARGET}

$(TARGET): $(OBJ_FILES)
	@echo "Linking..."
	$(CC) $(WARN) $(OFLAGS) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $@ $(LDLIBS) 
	@echo "Done."

obj/%.o: %.cpp
	@echo "Compiling "$<"..."
	$(CC) -c $(WARN) $(OFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@

objdir:
	@echo "Creating object directory..."
	mkdir -p $(OBJDIR)

clean: 
	@echo "Cleaning..."
	rm -rf $(OBJDIR)/*.o

mrproper: clean
	rm -rf $(TEST_DIR)/libgtest.a
	rm -rf ${TARGET}

test: $(TEST_DIR)/libgtest.a
	@echo "Compiling tests..."
	@echo "Running tests..."

$(TEST_DIR)/libgtest.a:
	@echo "Building test library..."
	$(CC) -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc -o $(OBJDIR)/gtest-all.o
	$(AR) -rv $(TEST_DIR)/libgtest.a $(OBJDIR)/gtest-all.o

install:
	@echo "Installing..."

doc:
	@echo "Building documentation..."
