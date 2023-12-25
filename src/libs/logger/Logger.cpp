#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "./Logger.h"

namespace Auoi {

    void Logger::verbose(const char *format, ...) {
        va_list args;
        va_start(args, format);

        Logger::printTimestamp(stdout);
        vfprintf(stdout, format, args);
        fprintf(stdout, "\n");

        va_end(args);
    }

    void Logger::info(const char *format, ...) {
        va_list args;
        va_start(args, format);

        // ANSI 이스케이프 코드로 파란색 텍스트 출력
        fprintf(stdout, "\033[1;34m"); // 1은 굵게, 34은 파란색
        Logger::printTimestamp(stdout);
        vfprintf(stdout, format, args);
        fprintf(stdout, "\033[0m\n"); // 스타일 초기화

        va_end(args);
    }

    void Logger::error(const char *format, ...) {
        va_list args;
        va_start(args, format);

        // ANSI 이스케이프 코드로 파란색 텍스트 출력
        fprintf(stderr, "\033[1;31m"); // 1은 굵게, 31은 빨간색
        Logger::printTimestamp(stderr);
        vfprintf(stderr, format, args);
        fprintf(stderr, "\033[0m\n"); // 스타일 초기화

        va_end(args);
    }

    void Logger::printTimestamp(FILE *file) {
        std::time_t now = std::time(0);
        std::tm* localTime = std::localtime(&now);

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S %Z", localTime);

        fprintf(file, "[%s] ", buffer);
    }
}
