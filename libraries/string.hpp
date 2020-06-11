
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

    // Operator version of stream method.
    friend inline std::ostream& operator<<(std::ostream& os, const jet::string& jetstr);

    // Retrieves a string from the file into a std::string.
    inline std::string value() const {
      std::stringstream ss;
      ss << *this;
      return ss.str();
    }

  protected:
    // Retrieves a string from the file into a std::ostream.
    inline std::ostream& stream(std::ostream& os) const {
      auto c { ' ' };

      while (true) {
        file >> std::noskipws >> c;
        
        if (c == '\0')
          break;
        if (file.eof())
          throw std::runtime_error { "End of file reached." };
        
        os << c;
      }

      return os;
    }
    
    private:
      std::fstream& file;

  };

  inline std::ostream& operator<<(std::ostream& os, const jet::string& jetstr) {
    return jetstr.stream(os);
  }

}

#endif
