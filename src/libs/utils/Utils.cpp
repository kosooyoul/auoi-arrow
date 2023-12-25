#include <random>
#include <sstream>
 #include <string>
#include <unordered_map>
#include <iostream>
#include <openssl/md5.h>
#include <iomanip>

#include "./Utils.h"

namespace Auoi {

    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string Utils::hash(const std::string& input) {
        MD5_CTX ctx;
        MD5_Init(&ctx);
        MD5_Update(&ctx, input.c_str(), input.length());

        unsigned char result[MD5_DIGEST_LENGTH];
        MD5_Final(result, &ctx);

        std::stringstream ss;
        for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(result[i]);
        }

        return ss.str();
    }

    std::string Utils::generateUUID() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }

}
