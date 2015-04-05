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

# Colors
black	= `tput setaf 0`
red		= `tput setaf 1`
green	= `tput setaf 2`
yellow	= `tput setaf 3`
blue	= `tput setaf 4`
magenta = `tput setaf 5`
cyan	= `tput setaf 2`
white	= `tput setaf 7`
reset	= `tput sgr0`

# Varibales to build the test library

GTEST_DIR	= test/googletest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

TEST_CPPFLAGS += -isystem $(GTEST_DIR)/include
TEST_CXXFLAGS += -g -Wall -Wextra -pthread

# Variable to build the tests

TEST_DIR	= test
TEST_EXEC 	= $(TEST_DIR)/test
TEST_SRCS	= $(wildcard test/*.cpp)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_DIR)/%.o,$(TEST_SRCS))

all: ${TARGET}

$(TARGET): $(OBJ_FILES)
	@echo "$(blue)Linking...$(reset)"
	$(CC) $(WARN) $(OFLAGS) $(CFLAGS) $(LDFLAGS) $(OBJ_FILES) -o $@ $(LDLIBS) 
	@echo "$(green)Done.$(reset)"

obj/%.o: %.cpp $(OBJDIR)
	@echo "$(blue)Compiling $(yellow)"$<"$(blue)...$(reset)"
	$(CC) -c $(WARN) $(OFLAGS) $(CFLAGS) $(LDFLAGS) $< -o $@

$(OBJDIR):
	@echo "$(blue)Creating object directory..."$(reset)
	mkdir -p $(OBJDIR)

clean: 
	@echo "$(blue)Cleaning objects...$(reset)"
	rm -rf $(OBJDIR)/*.o
	rm -rf $(TEST_DIR)/*.o

mrproper: clean
	@echo "$(blue)Cleaning executables...$(reset)"
	rm -rf $(TEST_DIR)/libgtest.a
	rm -rf $(TEST_DIR)/gtest_main.a
	rm -rf $(TEST_EXEC)
	rm -rf ${TARGET}

test: $(TEST_EXEC)
	@$(TEST_DIR)/test | sed "s/FAILED/$(red)FAILED$(reset)/g" | sed "s/OK/$(green)OK$(reset)/g" | sed "s/PASSED/$(green)PASSED$(reset)/g" | sed "s/RUN/$(blue)RUN$(reset)/g"
	@echo "$(green)Done.$(reset)"

$(TEST_EXEC): $(filter-out $(OBJDIR)/main.o, $(OBJ_FILES)) $(TEST_DIR)/libgtest.a $(TEST_DIR)/gtest_main.a
	@echo "$(blue)Compiling the test executable...$(reset)"
	@echo "$(cyan)Linking the test executable with the following objects: $(yellow)$^$(reset)."
	$(CC) $(TEST_DIR)/test.cpp $(CFLAGS) $^ $(TEST_CXXFLAGS) -o $(TEST_EXEC)

$(TEST_DIR)/libgtest.a:
	@echo "$(blue)Building test library...$(reset)"
	$(CC) $(TEST_CPPFLAGS) -I$(GTEST_DIR) $(TEST_CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $(OBJDIR)/gtest-all.o
	$(AR) -rv $(TEST_DIR)/libgtest.a $(OBJDIR)/gtest-all.o

$(TEST_DIR)/gtest_main.a:
	@echo "$(blue)Building the test runner...$(reset)"
	$(CC) $(TEST_CPPFLAGS) -I$(GTEST_DIR) $(TEST_CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $(OBJDIR)/gtest-main.o
	$(AR) -rv $(TEST_DIR)/gtest_main.a $(OBJDIR)/gtest-main.o

install:
	@echo "$(blue)Installing...$(reset)"

doc:
	@echo "$(blue)Building documentation...$(reset)"

