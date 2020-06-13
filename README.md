
# `jet`
Persist or retrieve strings over streams.

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

To clean the environment, build and run a driver {string, vector, pair, map} though `make`:
```shell
$ make DRV=string
```

---

## `jet::string`
Persist or retrieve a string over a stream. The string driver provides an example of usage:

Partial view of `drivers/string.cpp`
```C++
// Persist a string into the stream.
auto persist_path { "./test.str" };
auto persist_mode { std::iostream::out | std::iostream::trunc };
std::fstream persist_file { persist_path, persist_mode };

jet::string { persist_file, true } << "rec \\0 rec ~\0~ !rec";

// Force sync with underlying device so that the read occurs after the write.
persist_file.flush();

// Retrieves the recorded string from the stream as a string stream.
auto retrieve_path { "./test.str" };
auto retrieve_mode { std::iostream::in };
std::fstream retrieve_file { retrieve_path, retrieve_mode };

std::cout << jet::string { retrieve_file, true } << std::endl;
```

`stdout`
```
rec \0 rec ~
```

The `jet::string` constructor receives the stream to persist or retrieve strings and a boolean wheter to use breaklines for human readbility. Default is false.

### How it works?
The `jet::string` class is constructed with a stream reference. Once a persist command is issued, the `jet::string` instance will attempt to write the `std::string` into the stream, followed by a **null terminator** character `'\0'`. The `jet::string` object is then returned to enable sequential writes:

```C++
jet::string { file } << "cogno" << "coder";
```

The retrieve method will attempt to read the stream, a character at a time, until a null terminator character is found. A `std::runtime_error` is thrown if the end of file is reached before a null terminator character.

A `jet::string` can be retrieved into a output stream. The retrieve method returns the output stream, if used against one, in order to enable sequential stream data flow:

```C++
std::cout << jet::string { retrieve_file } << "data flow" << std::endl;
```

A `std::string` can be retrieved using the `value` method:
```C++
std::string str { jet::string { retrieve_file }.value() };
```

---

## `jet::vector`
Persist or retrieve a vector of strings over a stream. The `vector` driver provides an example of usage:

Partial view of `drivers/vector.cpp`
```C++
// Persist a vector of strings into the stream.
jet::vector { persist_file, true } << std::vector<std::string> { 
  "jet" , "cogno", "coder"
};

// Retrieves the recorded vector of strings from the stream.
auto vector { jet::vector { retrieve_file, true }.value() };
for (const auto& str: vector)
  std::cout << str;

std::cout << std::endl;
```

`stdout`
```
jet
cogno
coder
```

The variable `vector` type is `std::vector<std::string>`. The `jet::vector::value` method receives the number of strings *n* to retrieve. If *n* is less or equals than zero, `jet::vector` retrieve strings until it reaches the end of stream. It will read *n* strings or stop at end of stream, otherwise.


---

## `jet::pair`
Persist or retrieve a pair of strings over a stream. The `pair` driver provides an example of usage:

Partial view of `drivers/partial.cpp`
```C++
// Persist a pair of strings into the stream.
jet::pair { persist_file, true } << std::make_pair ( "first", "second" );

// Retrieves the recorded pair of strings from the stream.
auto pair { jet::pair { retrieve_file, true }.value() };
std::cout << pair.first << pair.second << std::endl;
```

`stdout`
```
first
second
```

The variable `pair` type is `std::pair<std::string,std::string>`.

---

## `jet::map`
Persist or retrieve a map of strings over a stream. The `map` driver provides an example of usage:

Partial view of `drivers/map.cpp`
```C++
// Persist a map of strings into the stream.
jet::map { persist_file, true } << std::map<std::string,std::string> { 
  std::make_pair ( "1. key", "1. value" ),
  std::make_pair ( "2. key", "2. value" ),
  std::make_pair ( "3. key", "3. value" ) 
};

// Retrieves the recorded map of strings from the stream.
auto map { jet::map { retrieve_file, true }.value() };
for (const auto& pair: map)
  std::cout << pair.first << pair.second;

std::cout << std::endl;
```

`stdout`
```
1. key
1. value
2. key
2. value
3. key
3. value
```

The variable `map` type is `std::map<std::string,std::string>`. The `jet::map::value` method receives the number of pairs *n* to retrieve. If *n* is less or equals than zero, `jet::map` retrieve pairs until it reaches the end of stream. It will read *n* pairs or stop at end of stream, otherwise.
