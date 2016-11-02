#pragma once
#include <string>

#if !defined(TK_LOG_LEVEL)
#   define TK_LOG_LEVEL tk::core::Debug
#endif

#define tk_assert(cond, msg) if (!(cond)) { tk::core::log(msg, tk::core::Error); }
#define tk_warn(cond, msg) if (!(cond)) { tk::core::log(msg, tk::core::Warning); }
#define tk_info(msg) if (tk::core::Info >= TK_LOG_LEVEL) { tk::core::log(msg, tk::core::Info); }
#define tk_debug(msg) if (tk::core::Debug >= TK_LOG_LEVEL) { tk::core::log(msg, tk::core::Debug); }

namespace tk {
    namespace core {

        enum LogLevel {
            Debug,
            Info,
            Warning,
            Error
        };

        void initLog(const std::string& filename);

        void log(const std::string& msg, LogLevel level = Debug);

    }
}

