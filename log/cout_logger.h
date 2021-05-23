#ifndef LOG_COUT_LOGGER_H
#define LOG_COUT_LOGGER_H

#include <chrono>
#include <cstring>
#include <iostream>
#include <unordered_map>

#include "logger.h"

namespace Log
{
  class cout_logger : public logger
  {
   public:
    cout_logger() = default;
    explicit cout_logger(const Severity& _showFileLocation, size_t _reserveOverhead = 64) :
      m_reserveOverhead(_reserveOverhead), m_showFileLocation(_showFileLocation)
    {
    }
    virtual ~cout_logger() override = default;

    virtual void log(
      const std::string& _msg, const Severity& _severity,
      const source_location& _location = source_location::current()) override
    {
      // Calculate the reserve size of string ahead of creating one
      size_t reserve_size = _msg.size() + m_reserveOverhead;

      // Severity String
      const char* severity_str = getSeverityStr(_severity);
      reserve_size += strlen(severity_str);

      // Text Colour
      auto text_col        = m_severityTextCol.find(_severity);
      bool update_text_col = text_col != m_severityTextCol.cend();

      if (update_text_col)
      {
        reserve_size += strlen(text_col->second) + strlen(defaultConsole());
      }

      // Create output string and reserve space
      std::string output;
      output.reserve(reserve_size);

      // Set text colour
      if (update_text_col)
      {
        output.append(text_col->second);
      }

      // Add severity string & timestamp
      output.push_back('[');
      output.append(severity_str);
      output.append(getTimeStamp());
      output.push_back(']');

      // Reset console colours if they were updated previously
      if (update_text_col)
      {
        output.append(defaultConsole());
      }

      // File Location
      if (_severity >= m_showFileLocation)
      {
        output.push_back(' ');
        output.append(getLocation(_location));
      }

      // Log message
      output.push_back(' ');
      output.append(_msg);
      output.push_back('\n');

      std::cout << output;
      std::cout.flush();
    }

    /**
     * \brief default amount of space to reserve for strings
     * */
    const size_t m_reserveOverhead = 64;

    /**
     * \brief Show file location if log level is >= to this value (0 for all)
     * */
    const Severity m_showFileLocation = LOG_WARNING;

    /* Console Colours */
    static inline constexpr const char* defaultConsole() { return "\033[0m"; }

    std::unordered_map<Severity, const char*> m_severityTextCol = {
      { Severity::LOG_INFO, "\033[1;32m" },    // Green
      { Severity::LOG_DEBUG, "\033[1;34m" },   // Blue
      { Severity::LOG_WARNING, "\033[1;33m" }, // Yellow
      { Severity::LOG_ERROR, "\033[1;31m" },   // Red
      { Severity::LOG_FATAL, "\033[1;41m" }    // Red Background
    };
  };
}

#endif // LOG_COUT_LOGGER_H
