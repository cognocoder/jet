
LIB := jet.hpp string.hpp vector.hpp pair.hpp map.hpp

.PHONY: build
build: clean jet

jet: $(LIB) drivers/jet.cpp
	g++ $? -std=c++20 -o jet

.PHONY: clean
clean:
	rm jet

PREFIX ?= /usr

.PHONY: install
install: jet 
	mkdir -p $(DESTDIR)$(PREFIX)/include/jet
	install -Dm755 jet $(DESTDIR)$(PREFIX)/bin/jet
	install -Dm644 $(foreach file, $(LIB), $(file)) $(DESTDIR)$(PREFIX)/include/jet/

.PHONY: uninstall
uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/include/jet
	rm $(DESTDIR)$(PREFIX)/bin/jet

