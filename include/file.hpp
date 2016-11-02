#pragma once

#include <string>
#include <linkage.hpp>

namespace tk {
    namespace core {

        /**
         * Read in a text file and return its entire contents as a string.
         * \param filename The file to read the contents from.
         * \return The contents of the specified file. Empty if the file does not exist.
         */
        TK_CORE std::string readFile(const std::string& filename);

    }
}
