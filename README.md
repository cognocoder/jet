# `jet`
Persist or retrieve a string, string pair or string map over a file.

## Package Layout
This project adopts an artesanal, minimalist, rolling release, driver based, public headers first `C++` [package layout](), distributed with a commented `makefile`.

---

### Usage
Just add the jet container folder to the *include path* and include the `jet.hpp` file.
```C++
#include <jet/jet.hpp>
```

### Build
To keep a translation unit up to date with `jet` headers and sources, list the makefile's `PKG`, `LIB` and `SRC` variables to its dependencies. Namelly:
```makefile
target: ... jet/jet.hpp jet/libraries/string.hpp ...
  actions
```

---

## `jet::string`
Persist or retrieve a string over a file. Driver string provides an example of usage:

`drivers/string.cpp`
```C++
#include "../jet.hpp"

#include <fstream>
#include <iostream>

int main() {
  // Persist a string into the file.
  auto persist_path { "./test.str" };
  auto persist_mode { std::fstream::out | std::fstream::trunc };
  std::fstream persist_file { persist_path, persist_mode };
  jet::string { persist_file } << "rec \\0 rec ~\0~ !rec";

  // Force sync with underlying device so that the read occurs after the write.
  persist_file.flush();

  // Retrieves the recorded string from the file as a string stream.
  auto retrieve_path { "./test.str" };
  auto retrieve_mode { std::fstream::in };
  std::fstream retrieve_file { retrieve_path, retrieve_mode };
  std::cout << jet::string { retrieve_file } << std::endl;

  return 0;
}
```
`stdout`
```
rec \0 rec ~
```

---

## `jet::pair`
Comming soon.

---

## `jet::map`
Comming soon.
