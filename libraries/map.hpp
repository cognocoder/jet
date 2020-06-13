
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
    map(std::fstream& file, bool breakline = false) :
        jet::pair{file, breakline}, file{file} {}

    // Persists a map of strings into the file.
    inline jet::map operator<<
        (const std::map<std::string,std::string>& map) const {
      for (const auto& pair: map) {
        jet::string::operator<<(pair.first);
        jet::string::operator<<(pair.second);
      }
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
          map.insert({ jet::string::value(), jet::string::value() });
        }
      } catch (std::runtime_error& err) { }

      return map;
    }

  private:
    std::fstream& file;
      
  };

  inline std::ostream& operator<<(std::ostream& os, const jet::map& jetmap) {
    try {
      while (true) {
        jetmap.stream(os);
        jetmap.stream(os);
      }
    } catch (std::runtime_error& err) { }
    
    return os;
  }

}

#endif
