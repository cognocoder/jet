
#ifndef _JET_VECTOR_HPP_
#define _JET_VECTOR_HPP_

#include <vector>

#include "string.hpp"

// Jet namespace.
namespace jet {

  // Persist or retrieve a vector of strings over a file.
  class vector : public jet::string {
  public:
    // Constructor for jet::vector.
    vector(std::iostream& file, bool breakline = false) :
        jet::string{file, breakline}, file{file} {}

    // Persists a vector of strings into the file.
    inline jet::vector operator<<
        (const std::vector<std::string>& vector) const {
      for (const auto& str: vector)
        jet::string::operator<<(str);
      return *this;
    }

    // Retrieves a vector of strings from the file into a std::ostream.
    friend inline std::ostream& operator<<
        (std::ostream& os, const jet::vector& jetvector);

    // Retrieves a vector of strings from the file into a std::vector.
    inline std::vector<std::string> value(int n = 0) const {
      std::vector<std::string> vector;
      
      try {
        if (n <= 0)
          while (true)
            vector.push_back({ jet::string::value() });
        else
          while (n--)
            vector.push_back({ jet::string::value() });
      } catch (std::runtime_error& err) { }

      return vector;
    }

  private:
    std::iostream& file;
      
  };

  inline std::ostream& operator<<
      (std::ostream& os, const jet::vector& jetvector) {
    try {
      while (true)
        jetvector.stream(os);
    } catch (std::runtime_error& err) { }
    
    return os;
  }

}

#endif
