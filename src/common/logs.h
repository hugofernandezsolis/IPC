/**
 * @copyright Copyright (c) 2023
 * 
 * @author Hugo Fernandez Solis (hugofernandezsolis@gmail.com)
 * @date 02-12-2023
 * 
 * @file Logs.h
 * 
 * @brief Macros and functions to help creating logs.
 */


#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>


namespace {

  // Helper macro to extract only the function name from __PRETTY_FUNCTION__
  #define FUNCTION_NAME \
    []() -> std::string { \
      std::string prettyFunction = __PRETTY_FUNCTION__; \
      size_t start = prettyFunction.find_first_of('('); \
      size_t end = prettyFunction.find_last_of(')'); \
      return prettyFunction.substr(0, start) + prettyFunction.substr(end + 2); \
    }()

  std::string currentDateTime() {
      auto now = std::chrono::system_clock::now();
      auto time_t = std::chrono::system_clock::to_time_t(now);
      std::tm tm_time = *std::localtime(&time_t);
      
      std::ostringstream oss;
      oss << std::put_time(&tm_time, "%d-%m-%Y %H:%M:%S");
      return oss.str();
  }
}


#define LOG_INFO2 LogHandler::oFileStream << '\n' << currentDateTime() << " " << FUNCTION_NAME << ": "
