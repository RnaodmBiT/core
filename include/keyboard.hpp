#pragma once

#include <event.hpp>
#include <unordered_map>

namespace tk {
    namespace core {

        class Keyboard {
            std::unordered_map<int, bool> states;
        public:

            Event<int> keyPress;
            Event<int> keyRelease;

            bool isKeyDown(int key) {
                return states.count(key) ? states[key] : false;
            }

            void handleEvent(int key, bool pressed) {
                if (pressed && !isKeyDown(key)) {
                    keyPress(key);
                }
                if (!pressed && isKeyDown(key)) {
                    keyRelease(key);
                }
                states[key] = pressed;
            }
        };

    }
}