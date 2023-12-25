#pragma once

namespace Auoi {

    class Logger {

        public:
            static void verbose(const char *format, ...);
            static void info(const char *format, ...);
            static void error(const char *format, ...);

        private:
            static void printTimestamp(FILE *file);

    };

}
