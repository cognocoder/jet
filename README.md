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

To clean the environment, build and run the string driver though `make`:
```shell
$ make DRV=string
```

---

## `jet::string`
Persist or retrieve a string over a file. The string driver provides an example of usage:

Partial view of `drivers/string.cpp`
```C++
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
```

`stdout`
```
rec \0 rec ~
```

### How it works?
The `jet::string` class is constructed with a file stream reference. Once a persist command is issued, the `jet::string` instance will attempt to write the `std::string` into the file, followed by a **null terminator** character `'\0'`. The `jet::string` object is then returned to enable sequential writes:

```C++
jet::string { file } << "cogno" << "coder";
```

The retrieve method will attempt to read the file, a character at a time, until a null terminator character is found. A `std::runtime_error` is thrown if the end of file is reached before a null terminator character.

A `jet::string` can be retrieved into a output stream `std::ostream` or a `std::string`. The retrieve method returns the output stream, if used against one, in order to enable sequential stream data flow:

```C++
  std::cout << jet::string { retrieve_file } << "data flow" << std::endl;
```

A `std::string` can be retrieved using the `value` method:
```C++
  std::string str { jet::string { retrieve_file }.value() };
```

---

## `jet::pair`
Persist or retrieve a pair of strings over a file. The `pair` driver provides an example of usage:

Partial view of `drivers/partial.cpp`
```C++
// Persist a pair of strings into the file.
auto persist_path { "./test.str" };
auto persist_mode { std::fstream::out | std::fstream::trunc };
std::fstream persist_file { persist_path, persist_mode };
jet::pair { persist_file } << std::make_pair ( "1. first", "2. second" );

// Force sync with underlying device so that the read occurs after the write.
persist_file.flush();

// Retrieves the recorded pair of strings from the file through a stream.
auto retrieve_path { "./test.str" };
auto retrieve_mode { std::fstream::in };
std::fstream retrieve_file { retrieve_path, retrieve_mode };
std::cout << jet::pair { retrieve_file } << std::endl;
```

`stdout`
```
jet::pair 0x...
    first 1. first
   second 2. second
```

---

## `jet::map`
Persist or retrieve a map of strings over a file. The `map` driver provides an example of usage:

Partial view of `drivers/map.cpp`
```C++
// Persist a map of strings into the file.
auto persist_path { "./test.str" };
auto persist_mode { std::fstream::out | std::fstream::trunc };
std::fstream persist_file { persist_path, persist_mode };
jet::map { persist_file } << std::map<std::string,std::string> { 
  std::make_pair ( "1. key", "1. value" ),
  std::make_pair ( "2. key", "2. value" ),
  std::make_pair ( "3. key", "3. value" ) 
};

// Force sync with underlying device so that the read occurs after the write.
persist_file.flush();

// Retrieves the recorded map of strings from the file through a stream.
auto retrieve_path { "./test.str" };
auto retrieve_mode { std::fstream::in };
std::fstream retrieve_file { retrieve_path, retrieve_mode };
std::cout << jet::map { retrieve_file } << std::endl;
```

`stdout`
```
jet::map 0x7fff93d23900

     key 1. key
   value 1. value

     key 2. key
   value 2. value

     key 3. key
   value 3. value
```
