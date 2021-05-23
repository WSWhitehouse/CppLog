#ifndef CPP_LOG_H
#define CPP_LOG_H

#include <iostream>
#include <string>

namespace Log
{
  enum class Severity : int
  {
    LOG_INVALID = -1,
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
  };

  static inline void str(const std::string& _str) { std::cout << _str << std::endl; }

} // namespace Log
#endif // CPP_LOG_H
