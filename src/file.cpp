#include <file.hpp>
#include <fstream>

namespace tk {
    namespace core {

        std::string readFile(const std::string& filename) {
            std::ifstream t(filename.c_str());
            std::string str;

            t.seekg(0, std::ios::end);
            str.reserve(t.tellg());
            t.seekg(0, std::ios::beg);

            str.assign((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
            return str;
        }

    }
}
