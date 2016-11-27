#pragma once
#include <linkage.hpp>

namespace tk {
    namespace core {
        class TK_CORE UpdateTimer {
            class Impl;
            Impl* impl;
        public:
            UpdateTimer(float frequency);
            ~UpdateTimer();

            bool update();
            float period();
        };
    }
}