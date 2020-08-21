
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
	cp jet $(DESTDIR)$(PREFIX)/bin/jet
	chmod 755 $(DESTDIR)$(PREFIX)/bin/jet
	cp $(foreach file, $(LIB), $(file)) $(DESTDIR)$(PREFIX)/include/jet/
	chmod 644 $(DESTDIR)$(PREFIX)/include/jet/*.hpp

.PHONY: uninstall
uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/include/jet
	rm $(DESTDIR)$(PREFIX)/bin/jet

