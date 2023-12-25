#pragma once

namespace Auoi {

    class Logger {

        public:
            static void vervose(const char *format, ...);
            static void info(const char *format, ...);
            static void error(const char *format, ...);

    };

}
