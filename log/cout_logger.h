#ifndef LOG_COUT_LOGGER_H
#define LOG_COUT_LOGGER_H

#include <unordered_map>

#include "logger.h"

namespace Log
{
  class cout_logger : private logger
  {
   public:
    cout_logger()                   = default;
    virtual ~cout_logger() override = default;

    virtual void log(
      const std::string& _msg, const Severity& _severity,
      const source_location& _location = source_location::current()) override
    {
      std::cout << generateMsg(_msg, _severity, _location);
      std::cout.flush();
    }

   private:
    std::string
    generateMsg(const std::string& _msg, const Severity& _severity, const source_location& _location)
    {
      return getSeverity(_severity) + _msg + " " + defaultConsole() + "\n";
    }

    std::string getSeverity(const Severity& _severity)
    {
      std::string severity;

      // Set text colour
      auto text_col = m_severityTextCol.find(_severity);
      if (text_col != m_severityTextCol.cend())
      {
        severity = text_col->second;
      }
      else
      {
        severity = defaultTextCol();
      }

      // Set background colour
      auto bg_col = m_severityBackgroundCol.find(_severity);
      if (bg_col != m_severityBackgroundCol.cend())
      {
        severity = bg_col->second;
      }

      // Add severity string
      severity += getSeverityStr(_severity);

      // Reset text colour
      severity += defaultTextCol();

      return severity;
    }

    /* Console Colours */
    static inline constexpr const char* defaultConsole() { return "\033[0m"; }
    static inline constexpr const char* defaultTextCol() { return "\033[1;37m"; } // White

    static inline const std::unordered_map<Severity, const char*> m_severityTextCol = {
      { Severity::LOG_INFO, "\033[1;32m" },     // Green
      { Severity::LOG_DEBUG, "\033[1;34m" },    // Blue
      { Severity::LOG_WARNING, "\033[1;33m" },  // Yellow
      { Severity::LOG_ERROR, "\033[1;31m" },    // Red
      { Severity::LOG_FATAL, defaultTextCol()} // Default
    };

    static inline const std::unordered_map<Severity, const char*> m_severityBackgroundCol = {
      { Severity::LOG_FATAL, "\033[1;41m" } // Red
    };
  };
}

#endif // LOG_COUT_LOGGER_H
