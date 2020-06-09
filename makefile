
BIN := jet

CFLAGS := -Wall -Wextra -Werror -Wfatal-errors -pedantic -pedantic-errors
CFLAGS += -std=c++17

PKG := jet.hpp

.PHONY: build driver clean run all

build: $(PKG)
	@g++ $? $(CFLAGS) -c -o $(BIN).o

driver: $(PKG) drivers/$(DRV).cpp
	@g++ $? $(CFLAGS) -o $(BIN)

clean:
	@rm -rf $(BIN) $(BIN).o *.str
	
all: clean run

run: $(BIN)
	@./$(BIN)
