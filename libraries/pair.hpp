
#ifndef _JET_PAIR_HPP_
#define _JET_PAIR_HPP_

#include <utility>

#include "string.hpp"

// Jet namespace.
namespace jet {

  // Persist or retrieve a pair of strings over a file.
  class pair : public jet::string {
  public:
    // Constructor for jet::pair.
    pair(std::fstream& file, bool breakline = false) : 
        jet::string{file, breakline}, file{file} {}

    // Persists a pair of strings into the file.
    inline jet::pair operator<<
        (const std::pair<std::string,std::string>& pair) const {
      jet::string::operator<<(pair.first);
      jet::string::operator<<(pair.second);
      return *this;
    }

    // Retrieves a pair of strings from the file into a std::ostream.
    friend inline std::ostream& operator<<
        (std::ostream& os, const jet::pair& jetpair);

    // Retrieves a pair of strings from the file into a std::pair.
    inline std::pair<std::string,std::string> value() const {
      return { jet::string::value(), jet::string::value() };
    }

  private:
    std::fstream& file;
      
  };

  inline std::ostream& operator<<(std::ostream& os, const jet::pair& jetpair) {
    jetpair.stream(os);
    jetpair.stream(os);
    return os;
  }

}

#endif
