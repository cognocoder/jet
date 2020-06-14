
#include "../jet.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main() {
  // Persist a string into the file.
  auto persist_path { "./test.str" };
  auto persist_mode { std::iostream::out | std::iostream::trunc };
  std::fstream persist_file { persist_path, persist_mode };
  if (!persist_file)
    throw std::runtime_error { "couldn't open file for persistence" };

  jet::string { persist_file, true } << "rec \\0 rec ~\0~ !rec";

  // Force sync with underlying device so that the read occurs after the write.
  persist_file.flush();

  // Retrieves the recorded string from the file through a stream.
  auto retrieve_path { "./test.str" };
  auto retrieve_mode { std::iostream::in };
  std::fstream retrieve_file { retrieve_path, retrieve_mode };
  if (!retrieve_file)
    throw std::runtime_error { "couldn't open file for retrieval" };
  
  std::cout << jet::string { retrieve_file, true } << std::endl;

  return 0;
}
