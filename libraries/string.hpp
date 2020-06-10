
#ifndef _JET_STRING_HPP_
#define _JET_STRING_HPP_

#include <fstream>
#include <sstream>
#include <string>

// Jet namespace.
namespace jet {

  // Persist or retrieve a string over a file.
  class string {
  public:
    // Constructor for jet::string.
    explicit string(std::fstream& file) : file{file} {}

    // Persists a string into the file.
    inline string operator<<(const std::string& str) const {
      this->file << str << '\0';
      return *this;
    }

    // Retrieves a string from the file into a std::ostream.
    friend inline std::ostream& operator<<(std::ostream& os, const string& jetstr);

    // Retrieves a string from the file into a std::string.
    inline std::string str() const {
      std::stringstream ss;
      ss << *this;
      return ss.str();
    }

  private:
    std::fstream& file;
      
  };

  inline std::ostream& operator<<(std::ostream& os, const string& jetstr) {
    auto c { ' ' };

    while (true) {
      jetstr.file >> std::noskipws >> c;
      
      if (c == '\0')
        break;
      if (jetstr.file.eof())
        throw std::runtime_error { "End of file reached." };
      
      os << c;
    }

    return os;
  }

}

#endif
