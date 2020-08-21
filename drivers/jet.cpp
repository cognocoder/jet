
#include "../jet.hpp"

#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <map>
#include <filesystem>

int main(int argc, char* argv[]) {

  std::string file_name;

  bool out { true };
  bool in { true };
  bool help { false };
  bool delete_keys { false };

  bool no_file { true };

  std::unordered_set<std::string> options;
  
  for (int i = 1; i < argc; i++) {
    std::string str { argv[i] };
    if (str.find('-') != std::string::npos) {
      options.insert(str);
    }
    else {
      file_name = str;
      no_file = false;
    }
  }

  if (no_file)
    std::cerr << "Error: no file specified." << std::endl;

  if (options.contains("-h")) help = true;
  if (options.contains("--help")) help = true;


  if (options.contains("-no")) out = false;
  if (options.contains("-ni")) in = false;

  if (options.contains("-dk")) delete_keys = true;

  if (help) {
    std::cout << "jet usage: $ jet [options] file\n\n"
      " --help or\n"
      "  -h          Display this message.\n\n"
      "  -no         No output for data read from file.\n"
      "  -ni         No input for map from input stream.\n\n"
      "  -dk         Delete keys readed from input strem from map.\n\n"
      << std::endl;

    if (argc == 2)
      return 0;
  }

  auto path { std::filesystem::current_path().string() };
  auto file_mode { std::iostream::in };
  auto file_path { path + "/" + file_name };
  std::fstream ifile { file_path, file_mode };
  
  auto map {
    ifile ? jet::map { ifile }.value() : std::map<std::string, std::string>()
  };

  if (out) {
    std::cout << std::endl;
    for (const auto& pair: map)
      std::cout << "  " << pair.first << "\n  " << pair.second << "\n";
    std::cout << std::endl;
  }

  if (in) {
    auto file_mode { std::iostream::out | std::iostream::trunc };
    std::fstream ofile { file_path, file_mode };
    
    if (!ofile)
      throw std::runtime_error { "Error: "
        "couldn't open file for writing the map." };

    std::string key, value;
    while (!delete_keys) {
      std::cout << "  ";
      std::getline(std::cin, key);
      std::cout << "  ";
      std::getline(std::cin, value);

      if (std::cin.eof())
        break;

      auto pos { map.find(key) };

      if (pos == map.end())
        map.insert(std::make_pair(key,value));
      else
        pos->second = value;
    }

    while (delete_keys) {
      std::cout << "  ";
      std::getline(std::cin, key);

      if (std::cin.eof())
        break;

      map.erase(key);
    }

    jet::map { ofile } << map;
    ofile.flush();
  }

  std::cout << std::endl;

  return 0;
}

