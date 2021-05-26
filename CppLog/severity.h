#ifndef CPP_LOG_H
#define CPP_LOG_H

namespace Log
{
  enum Severity
  {
    LOG_INVALID = -1,
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
  };
} // namespace Log
#endif // CPP_LOG_H
