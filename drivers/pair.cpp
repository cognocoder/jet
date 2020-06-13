
#include "../jet.hpp"

#include <fstream>
#include <iostream>
#include <utility>

int main() {
  // Persist a pair of strings into the file.
  auto persist_path { "./test.str" };
  auto persist_mode { std::fstream::out | std::fstream::trunc };
  std::fstream persist_file { persist_path, persist_mode };
  
  jet::pair { persist_file, true } << std::make_pair ( "first", "second" );

  // Force sync with underlying device so that the read occurs after the write.
  persist_file.flush();

  // Retrieves the recorded pair of strings from the file through a stream.
  auto retrieve_path { "./test.str" };
  auto retrieve_mode { std::fstream::in };
  std::fstream retrieve_file { retrieve_path, retrieve_mode };
  
  auto pair { jet::pair { retrieve_file, true }.value() };
  std::cout << pair.first << pair.second << std::endl;
  
  return 0;
}
