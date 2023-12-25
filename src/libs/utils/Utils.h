#pragma once

namespace Auoi {

    class Utils {

        public:
            static std::string hash(const std::string& text);
            static std::string generateUUID();
            static std::string hexToBase62(const std::string& hexString);

    };

}
