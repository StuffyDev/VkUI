#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

class Log {
public:
    static void info(const std::string& message) {
        log("INFO", message, "\033[32m"); // Green
    }

    static void warn(const std::string& message) {
        log("WARN", message, "\033[33m"); // Yellow
    }

    static void error(const std::string& message) {
        log("ERROR", message, "\033[31m"); // Red
    }

private:
    static void log(const std::string& level, const std::string& message, const std::string& color) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        // [LEVEL] YYYY-MM-DD HH:MM:SS: message
        std::cout << color << "[" << level << "] "
                  << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
                  << ": " << message << "\033[0m" << std::endl;
    }
};
