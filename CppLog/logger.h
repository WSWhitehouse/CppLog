#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H

#include <iomanip>
#include <map>
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

    virtual void
    log_info(const std::string& _msg, const source_location& _location = source_location::current())
    {
      log(_msg, Severity::LOG_INFO, _location);
    }

    virtual void
    log_debug(const std::string& _msg, const source_location& _location = source_location::current())
    {
      log(_msg, Severity::LOG_DEBUG, _location);
    }

    virtual void log_warning(
      const std::string& _msg, const source_location& _location = source_location::current())
    {
      log(_msg, Severity::LOG_WARNING, _location);
    }

    virtual void
    log_error(const std::string& _msg, const source_location& _location = source_location::current())
    {
      log(_msg, Severity::LOG_ERROR, _location);
    }

    virtual void
    log_fatal(const std::string& _msg, const source_location& _location = source_location::current())
    {
      log(_msg, Severity::LOG_FATAL, _location);
    }

   protected:
    static const char* GetSeverityStr(const Severity& _severity)
    {
#if 0
      constexpr static const void* labels[] = {
        [Severity::LOG_INFO] = &&Info,       [Severity::LOG_DEBUG] = &&Debug,
        [Severity::LOG_WARNING] = &&Warning, [Severity::LOG_ERROR] = &&Error,
        [Severity::LOG_FATAL] = &&Fatal,
      };

      goto* labels[_severity];


      static std::unordered_map<Severity, const char*> sev = {
        { Severity::LOG_INFO, "INFO:  " },    { Severity::LOG_DEBUG, "DEBUG: " },
        { Severity::LOG_WARNING, "WARN:  " }, { Severity::LOG_ERROR, "ERROR: " },
        { Severity::LOG_FATAL, "FATAL: " },
      };
      return sev.at(_severity);
#endif

      switch (_severity)
      {
        case Log::Severity::LOG_INFO:
        Info:
          return "INFO:  ";
        case Log::Severity::LOG_DEBUG:
        Debug:
          return "DEBUG: ";
        case Log::Severity::LOG_WARNING:
        Warning:
          return "WARN:  ";
        case Log::Severity::LOG_ERROR:
        Error:
          return "ERROR: ";
        case Log::Severity::LOG_FATAL:
        Fatal:
          return "FATAL: ";
        case Log::Severity::LOG_INVALID:
        default:
        Invalid:
          return "";
      }
    }

    static std::string TimeStamp()
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

    static std::string Location(const source_location& _location, const size_t& _reserve)
    {
      if (_location.unsupported())
      {
        return {}; // Return empty string if location is unsupported
      }

      // Magic number (7) = amount of colons and line/col numbers
      size_t reserve = 7 + _reserve;
      std::string output;
      output.reserve(reserve);

      // File Name
      std::string file_name = _location.file_name();

      // Remove file path from start of file name
      auto index = file_name.find_last_of('/');
      output.append(index != std::string::npos ? file_name.substr(index + 1) : output);

      output.append(":");
      output.append(_location.function_name());
      output.append(":");
      output.append(std::to_string(_location.line()));
      output.append(":");
      output.append(std::to_string(_location.column()));
      return output;
    }
  };

} // namespace Log

#endif // LOG_LOGGER_H
