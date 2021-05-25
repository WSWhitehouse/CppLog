# Cpp Log
Simple header-only logging library for modern C++

## Getting Started

Copy the `log` folder into your build files and use a C++11 compiler.

## Logging

Logging requires a logger object to be created, in the example below it uses a cout logger. This logger outputs everything to the standard cout console.

```
#include "log/logger.h"
#include "log/cout_logger.h"

int main() 
{
    // Logger object
    Log::logger* logger = nullptr;
    
    // Create logger (in this case a cout logger)
    logger = new Log::cout_logger();
    
    // Log
    logger->log("Welcome to CppLog!", Log::Severity::LOG_INFO);
    logger->log("Modern C++ logger",  Log::Severity::LOG_DEBUG);
    logger->log("Supports warnings",  Log::Severity::LOG_WARNING);
    logger->log("error",              Log::Severity::LOG_ERROR);
    logger->log("fatal",              Log::Severity::LOG_FAFTAL);
    
    
    // Don't forget to clean up!
    delete logger;
}
```

## Features
- Log to the console
- Logs timestamp with message
- Create your own custom loggers 
