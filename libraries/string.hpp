
#ifndef _JET_STRING_HPP_
#define _JET_STRING_HPP_

#include <fstream>
#include <sstream>
#include <string>

// Jet namespace.
namespace jet {

  // Persist or retrieve a string over a file.
  class string {
  private:
    std::fstream& file;

  public:
    // Constructor for jet::string.
    explicit string(std::fstream& file) : file{file} {}

    // Persists a string into the file.
    inline string operator<<(const std::string& str) {
      this->file << str << '\0';
      return *this;
    }

    // Retrieves a string from the file into a ostream or a string.
    friend inline std::ostream& operator<<(std::ostream& os, const string& jetstr);
    friend inline std::string& operator<<(std::string& os, const string& jetstr);
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

  inline std::string& operator<<(std::string& str, const string& jetstr) {
    std::stringstream ss; 
    ss << jetstr;
    str = ss.str();
    return str;
  }
}

#endif
