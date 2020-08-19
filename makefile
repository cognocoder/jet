
# Executable file name.
BIN := jet

# Compiler flags.
CFLAGS := -std=c++20

# Default driver in use.
DRV := jet
# Package public header files.
PKG := jet.hpp
# Private header files.
LIB := string.hpp vector.hpp pair.hpp map.hpp

ARG :=

.PHONY: all clean driver run build install

# Since this is a header only library, default target will clean the 
# environment, build the default driver, and run it.
all: clean driver run

clean:
	@rm -rf $(BIN)
	
$(BIN): $(PKG) $(LIB) drivers/$(DRV).cpp
	@g++ $? $(CFLAGS) -o $(BIN)

run: $(BIN)
	@./$(BIN) $(ARG)

build: clean $(BIN)

install: $(BIN) $(PKG) $(LIB)
	@mkdir -p /usr/include/jet
	@cp $(foreach file, $(PKG), $(file)) /usr/include/jet/
	@cp $(foreach file, $(LIB), $(file)) /usr/include/jet/
	@cp $(foreach file, $(BIN), $(file)) /usr/bin/

uninstall:
	@rm -rf /usr/include/jet
	@rm /usr/bin/$(BIN)

