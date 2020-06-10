
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
