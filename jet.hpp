
#ifndef _JET_HPP_
#define _JET_HPP_

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
    string(std::fstream& file) : file{file} {}

    inline string& operator<<(const std::string& str) {
      string::file << str << '\0';
      return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const string& jetstr);
  };

  inline std::ostream& operator<<(std::ostream& os, const string& jetstr) {
    auto c { ' ' };

    while (true) {
      // Enable skipped characters to be read.
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
