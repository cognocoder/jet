
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
    explicit pair(std::fstream& file) : jet::string{file}, file{file} {}

    // Persists a pair of strings into the file.
    inline jet::pair operator<<
        (const std::pair<std::string,std::string>& pair) const {
      this->file << pair.first << '\0' << pair.second << '\0';
      return *this;
    }

    // Retrieves a pair of strings from the file into a std::ostream.
    friend inline std::ostream& operator<<
        (std::ostream& os, const jet::pair& jetpair);

    // Retrieves a pair of strings from the file into a std::pair.
    inline std::pair<std::string,std::string> value() const {
      std::stringstream ss1, ss2;
      stream(ss1);
      stream(ss2);
      return { ss1.str(), ss2.str() };
    }

  private:
    std::fstream& file;
      
  };

  inline std::ostream& operator<<(std::ostream& os, const jet::pair& jetpair) {
    os << "jet::pair " << &jetpair << "\n\n    first ";
    jetpair.stream(os) << "\n   second ";
    jetpair.stream(os);
    return os;
  }

}

#endif
