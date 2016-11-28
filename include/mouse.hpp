#pragma once

#include <event.hpp>
#include <unordered_map>

namespace tk {
    namespace core {

        class Mouse {
            std::unordered_map<int, bool> states;
        public:

            Event<int> buttonPress;
            Event<int> buttonRelease;

            int x, y, deltaX, deltaY;

            bool isButtonDown(int key) {
                return states.count(key) ? states[key] : false;
            }

            void handleEvent(int button, bool pressed) {
                if (pressed && !isButtonDown(button)) {
                    buttonPress(button);
                }
                if (!pressed && isButtonDown(button)) {
                    buttonRelease(button);
                }
                states[button] = pressed;
            }

            void handleMove(int mx, int my) {
                deltaX = mx - x;
                deltaY = my - y;
                x = mx;
                y = my;
            }
        };

    }
}