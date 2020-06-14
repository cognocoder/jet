
#include "../jet.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int main() {
  // Persist a vector of strings into the file.
  auto persist_path { "./test.str" };
  auto persist_mode { std::iostream::out | std::iostream::trunc };
  std::fstream persist_file { persist_path, persist_mode };
  if (!persist_file)
    throw std::runtime_error { "couldn't open file for persistence" };

  jet::vector { persist_file, true } << std::vector<std::string> { 
    "jet" , "cogno", "coder"
  };

  // Force sync with underlying device so that the read occurs after the write.
  persist_file.flush();

  // Retrieves the recorded map of strings from the file through a stream.
  auto retrieve_path { "./test.str" };
  auto retrieve_mode { std::iostream::in };
  std::fstream retrieve_file { retrieve_path, retrieve_mode }; 
  if (!retrieve_file)
    throw std::runtime_error { "couldn't open file for retrieval" };
  
  auto vector { jet::vector { retrieve_file, true }.value() };
  for (const auto& str: vector)
    std::cout << str;

  std::cout << std::endl;

  return 0;
}
