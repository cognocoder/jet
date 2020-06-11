
#ifndef _JET_MAP_HPP_
#define _JET_MAP_HPP_

#include <map>

#include "pair.hpp"

// Jet namespace.
namespace jet {

  // Persist or retrieve a pair of strings over a file.
  class map : public jet::pair {
  public:
    // Constructor for jet::pair.
    explicit map(std::fstream& file) : jet::pair{file}, file{file} {}

    // Persists a map of strings into the file.
    inline jet::map operator<<
        (const std::map<std::string,std::string>& map) const {
      for (const auto& pair: map)
        this->file << pair.first << '\0' << pair.second << '\0';
      return *this;
    }

    // Retrieves a map of strings from the file into a std::ostream.
    friend inline std::ostream& operator<<
        (std::ostream& os, const jet::map& jetmap);

    // Retrieves a map of strings from the file into a std::map.
    inline std::map<std::string,std::string> value() const {
      std::map<std::string,std::string> map;
      
      try {
        while (true) {
          std::stringstream ss1, ss2;
          stream(ss1);
          stream(ss2);
          map.insert({ ss1.str(), ss2.str() });
        }
      } catch (std::runtime_error& err) { }

      return map;
    }

  private:
    std::fstream& file;
      
  };

  inline std::ostream& operator<<(std::ostream& os, const jet::map& jetmap) {
    os << "jet::map " << &jetmap;
    
    try {
      while (true) {
        std::stringstream ss;
        ss << "\n\n     key ";
        jetmap.stream(ss) << "\n   value ";
        jetmap.stream(ss);
        os << ss.str();
      }
    } catch (std::runtime_error& err) { }
    
    return os;
  }

}

#endif
