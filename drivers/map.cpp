
#include "../jet.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
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

  return 0;
}
