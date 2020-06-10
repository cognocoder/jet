
# Executable file name.
BIN := jet

# Include directories.
INC := libraries

# Compiler flags.
CFLAGS := -I $(INC)
CFLAGS += -Wall -Wextra -Werror -Wfatal-errors -pedantic -pedantic-errors
CFLAGS += -std=c++17

# Default driver in use.
DRV := string
# Package public header files.
PKG := *.hpp
# Private header files.
LIB := $(INC)/*.hpp

.PHONY: all clean driver run 

# Since this is a header only library, default target will clean the 
# environment, build the default driver, and run it.
all: clean driver run

clean:
	@rm -rf $(BIN) *.str	
	
driver: $(PKG) $(LIB) drivers/$(DRV).cpp
	@g++ $? $(CFLAGS) -o $(BIN)

run: $(BIN)
	@./$(BIN)
