
#include "../jet.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  // Persist a map of strings into the file.
  auto persist_path { "./test.str" };
  auto persist_mode { std::iostream::out | std::iostream::trunc };
  std::fstream persist_file { persist_path, persist_mode };
  
  jet::map { persist_file, true } << std::map<std::string,std::string> { 
    std::make_pair ( "1. key", "1. value" ),
    std::make_pair ( "2. key", "2. value" ),
    std::make_pair ( "3. key", "3. value" ) 
  };

  // Force sync with underlying device so that the read occurs after the write.
  persist_file.flush();

  // Retrieves the recorded map of strings from the file through a stream.
  auto retrieve_path { "./test.str" };
  auto retrieve_mode { std::iostream::in };
  std::fstream retrieve_file { retrieve_path, retrieve_mode }; 

  auto map { jet::map { retrieve_file, true }.value() };
  for (const auto& pair: map)
    std::cout << pair.first << pair.second;

  std::cout << std::endl;

  return 0;
}
