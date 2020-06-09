
#include "../jet.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main() {
  auto persist_path { "./test.str" };
  auto persist_mode { std::fstream::out | std::fstream::trunc };
  std::fstream persist_file { persist_path, persist_mode };
  jet::string::persist(persist_file, "cognocoder");

  // Force sync with underlying device so that the read occurs after the write.
  persist_file.flush();

  auto retrieve_path { "./test.str" };
  auto retrieve_mode { std::fstream::in };
  std::fstream retrieve_file { retrieve_path, retrieve_mode };
  auto retrieve_str = jet::string::retrieve(retrieve_file);

  std::cout << retrieve_str << std::endl;;

  return 0;
}
