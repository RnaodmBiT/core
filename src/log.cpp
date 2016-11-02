#include <log.hpp>
#include <fstream>
#include <cstdlib>

namespace tk {
    namespace core {

        static std::ofstream logFile; 

        void initLog(const std::string& filename) {
            logFile.open(filename);
        }

        void log(const std::string& msg, LogLevel level) {
            switch (level) {
                case Debug:
                    logFile << "Debug: ";
                    printf("Debug: ");
                    break;
                case Info:
                    logFile << "Info: ";
                    printf("Info: ");
                    break;
                case Warning:
                    logFile << "Warning: ";
                    printf("Warning: ");
                    break;
                case Error:
                    logFile << "Error: ";
                    printf("Error: ");
                    break;
            }

            logFile << msg << std::endl;
            printf("%s\n", msg.c_str());

            if (level == Error) {
                exit(0);
            }
        }

    }
}
