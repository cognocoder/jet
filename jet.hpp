
#ifndef _JET_HPP_
#define _JET_HPP_

#include <fstream>
#include <sstream>
#include <string>

// Jet namespace.
namespace jet {

  // Jet string: persist and retrieve a string to or from a file.
  namespace string {

    // Writes a string followed by the null terminator character to the file.
    inline void persist(std::fstream& file, const std::string& str) {
      file << str << '\0';
    }

    // Reads a string from file.
    // Consumes the string and a null terminator character.
    inline std::string retrieve(std::fstream& file) {
      auto c { ' ' };
      std::stringstream ss;
      
      while (true) {

        // Enable skipped characters to be read.
        file >> std::noskipws >> c;
        
        if (c == '\0')
          break;
        if (file.eof())
          throw std::runtime_error { "End of file reached." };
        
        ss << c;
      }

      return ss.str();
    }

  }

}

#endif
