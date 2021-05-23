#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H

#include "log.h"
#include "source_location.h"

#include <string>

namespace Log
{
  class logger
  {
   public:
    logger()          = default;
    virtual ~logger() = default;

    virtual void log(
      const std::string& _msg, const Severity& _severity,
      const source_location& _location = source_location::current()) = 0;

   protected:
    const char* getSeverityStr(const Severity& _severity)
    {
      switch (_severity)
      {
        case Log::Severity::LOG_INFO:
          return " INFO: ";
        case Log::Severity::LOG_DEBUG:
          return " DEBUG: ";
        case Log::Severity::LOG_WARNING:
          return " WARNING: ";
        case Log::Severity::LOG_ERROR:
          return " ERROR: ";
        case Log::Severity::LOG_FATAL:
          return " FATAL: ";
        case Log::Severity::LOG_INVALID:
        default:
          return " UNKNOWN SEVERITY: ";
      }
    }
  };
} // namespace Log

#endif // LOG_LOGGER_H
