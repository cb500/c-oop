# -*- Makefile -*-

# CC    = gcc
CC    = clang
MKDIR = mkdir -p
VALGRIND = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all

# Binary name
BIN  	 = oop

# Folders and paths
SRC_DIR	  	= src
INC_DIR   	= ./include
BUILD_DIR 	= build


# CC flags and libs
CFLAG_BLOCKS  = -fblocks
CFLAGS 		  = -fPIC -Wall -Wextra -g -O0 -I$(INC_DIR) $(CFLAG_BLOCKS) -I/usr/include/block
LDFLAGS 	  = -lBlocksRuntime -ldispatch
LIBS   		  =

# Source files and object files
SRC_FILES  = $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(notdir $(SRC_FILES))))

SILENT := 

.PHONY: build test valgrind clean

build: directories $(BIN)
	@echo "Done, enjoy your binary files :D"

directories:
	@echo "Creating directories $(BUILD_DIR)"
	$(SILENT) $(MKDIR) $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling project file '$<' to create '$(BUILD_DIR)/$@'"
	$(SILENT) $(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

$(BIN): $(OBJ_FILES)
	@echo "Linking the object files ($^) to build '$(BUILD_DIR)/$@' executable file"
	$(SILENT) $(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)

test: directories $(BIN_TEST)
	@echo ""
	@echo "--- TESTS BEGIN ------------------------------------"
	$(BUILD_DIR)/$(BIN_TEST)
	@echo ""
	@echo "---- TESTS END --------------------------------------"
	@echo ""

valgrind:
	RET=0
	@echo "Checking binaries to run valgrind..."
ifneq ("$(wildcard $(BUILD_DIR)/$(BIN))","")
	@echo "Running valgrind against $(BUILD_DIR)/$(BIN)"
	$(SILENT) RET=`$(VALGRIND) --log-file=$(BUILD_DIR)/valgrind-$(BIN).txt $(BUILD_DIR)/$(BIN)`
	@echo "Done with valgrind! You can find the restult at $(BUILD_DIR)/valgrind-$(BIN).txt"
endif

ifneq ("$(wildcard $(BUILD_DIR)/$(BIN_TEST))","")
	@echo "Running valgrind against $(BUILD_DIR)/$(BIN_TEST)"
	$(SILENT) RET=`$(VALGRIND) --log-file=$(BUILD_DIR)/valgrind-$(BIN_TEST).txt $(BUILD_DIR)/$(BIN_TEST)`
	@echo "Done with valgrind! You can find the restult at $(BUILD_DIR)/valgrind-$(BIN_TEST).txt"
endif

coverage: $(CVG_FILE)

$(CVG_FILE): test
	@echo "Building coverage file $(BUILD_DIR)/$(CVG_FILE)"
	$(SILENT) $(GCOV) $(GCONV_FLAGS) -o $(BUILD_DIR)/$(CVG_FILE)

clean:
	$(SILENT) rm -Rf $(BUILD_DIR)