#pragma once
#include <string>
#include <sstream>

namespace tk {
    namespace core {

        static std::string format(const std::string& str) {
            return str;
        }

        template <class T, class ...U>
        std::string format(const std::string& str, const T& t, const U&... u) {
            auto i = str.find("%%");

            std::stringstream stream;
            stream << str.substr(0, i) << t << format(str.substr(i + 2), u...);
            return stream.str();
        }

        template <class T, int N>
        constexpr int sizeof_array(T(&)[N]) {
            return N;
        }

    }
}
