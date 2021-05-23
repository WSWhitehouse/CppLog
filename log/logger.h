#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H

#include <iomanip>
#include <string>

#include "severity.h"
#include "source_location.h"

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
          return "INFO:  ";
        case Log::Severity::LOG_DEBUG:
          return "DEBUG: ";
        case Log::Severity::LOG_WARNING:
          return "WARN:  ";
        case Log::Severity::LOG_ERROR:
          return "ERROR: ";
        case Log::Severity::LOG_FATAL:
          return "FATAL: ";
        case Log::Severity::LOG_INVALID:
        default:
          return "";
      }
    }

    std::string getTimeStamp()
    {
      struct std::tm current_time
      {
      };

      const auto now      = std::chrono::system_clock::now();
      const auto now_as_t = std::chrono::system_clock::to_time_t(now);
      const auto microseconds =
        std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

#ifdef _WIN32
      localtime_s(&current_time, &now_as_t);
#else
      localtime_r(&now_as_t, &current_time);
#endif

      std::ostringstream nowSs;
      nowSs << std::put_time(&current_time, "%Y-%m-%d %T") << '.' << std::setfill('0')
            << std::setw(6) << microseconds.count() << std::put_time(&current_time, "%z");

      auto time = nowSs.str();
      /* somewhat special - maybe see systemtimeformatter */
      time.replace(time.end() - 2, time.end() - 2, ":");
      return time;
    }

    std::string getLocation(const source_location& _location)
    {
      std::string location = _location.file_name();

      location.find_last_of('/');
      location.append(":");
      location.append(_location.function_name());
      location.append(":");
      location.append(std::to_string(_location.line()));
      location.append(":");
      location.append(std::to_string(_location.column()));
      return location;
    }
  };
} // namespace Log

#endif // LOG_LOGGER_H
