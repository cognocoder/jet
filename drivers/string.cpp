
#include "../jet.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main() {
  // Persist a string into the file.
  auto persist_path { "./test.str" };
  auto persist_mode { std::fstream::out | std::fstream::trunc };
  std::fstream persist_file { persist_path, persist_mode };
  
  jet::string { persist_file, true } << "rec \\0 rec ~\0~ !rec";

  // Force sync with underlying device so that the read occurs after the write.
  persist_file.flush();

  // Retrieves the recorded string from the file through a stream.
  auto retrieve_path { "./test.str" };
  auto retrieve_mode { std::fstream::in };
  std::fstream retrieve_file { retrieve_path, retrieve_mode };
  
  std::cout << jet::string { retrieve_file, true } << std::endl;

  return 0;
}
