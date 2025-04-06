#pragma once

#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


inline std::string current_timestamp() {
    using namespace std::chrono;

    auto now = system_clock::now();
    auto itt = system_clock::to_time_t(now);
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&itt), "%F %T") << '.' << std::setw(3) << std::setfill('0') << ms.count();
    return oss.str();
}

#define CTRL_HANDLER_MACRO()                                                      \
BOOL CtrlHandler(DWORD fdwCtrlType) {                                             \
    switch (fdwCtrlType) {                                                        \
        case CTRL_C_EVENT:                                                        \
            std::cout << "Ctrl + C pressed. Handling signal..." << std::endl;     \
            g_running = false;                                                    \
            return TRUE;                                                          \
        case CTRL_BREAK_EVENT:                                                    \
            std::cout << "Ctrl + Break pressed. Handling signal..." << std::endl; \
            g_running = false;                                                    \
            return TRUE;                                                          \
        default:                                                                  \
            return FALSE;                                                         \
    }                                                                             \
}

class Logger {

public:
    Logger(){}

    template<typename T>
    Logger& operator<<(const T& message) {
        m_message += message;
        return *this;
    }

    ~Logger() {
        const std::string timestamp = current_timestamp();
        std::cout << "[" << timestamp << "] " << m_message << std::endl;
    }

private:
    Logger(const Logger&) = delete;  // Disable copy constructor
    Logger& operator=(const Logger&) = delete;  // Disable copy assignment

    std::string m_message;
};

#define LOG Logger()
