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
#include <fstream>


namespace {

  // Helper macro to extract only the function name from __PRETTY_FUNCTION__
  #define FUNCTION_NAME \
    []() -> std::string { \
      std::string prettyFunction = __PRETTY_FUNCTION__; \
      size_t start = prettyFunction.find_first_of('('); \
      size_t end = prettyFunction.find_last_of(')'); \
      return prettyFunction.substr(0, start) + prettyFunction.substr(end + 2); \
    }()

  std::string get_current_date_and_time() {
      auto now = std::chrono::system_clock::now();
      auto time_t = std::chrono::system_clock::to_time_t(now);
      std::tm tm_time = *std::localtime(&time_t);
      
      std::ostringstream oss;
      oss << std::put_time(&tm_time, "%d-%m-%Y %H:%M:%S");
      return oss.str();
  }


  class LogHandler {
    public:
      LogHandler() {
        if (!oFileStream.is_open()) {
          oFileStream.open("~/logs/IPC/logs.txt");
        }
      }

      ~LogHandler() {
        if (oFileStream.is_open()) {
          oFileStream.close();
        }
      }
      
      static std::ofstream oFileStream;
  };

  std::ofstream LogHandler::oFileStream("~/logs/IPC/logs.txt");
}


#define LOG_INFO LogHandler::oFileStream << '\n' << get_current_date_and_time() << " " << FUNCTION_NAME << ": "

namespace aux {
  void test(void) {
    std::cout << "Entered test" << std::endl;
    LOG_INFO << "This is an info message";
  }
}

int main() {
  std::cout << "Init main" << std::endl;
  aux::test();
  std::cout << "Finish main" << std::endl;
  return 0;
}