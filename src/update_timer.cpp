#include "update_timer.hpp"
#include <chrono>
#include "log.hpp"
#include "utility.hpp"

namespace tk {
    namespace core {
        class UpdateTimer::Impl {
            typedef std::chrono::high_resolution_clock clock;

            std::chrono::time_point<clock> start;
            int updates;
            double frequency;

            long long requiredNumberOfUpdates() {
                std::chrono::nanoseconds time = clock::now() - start;
                double rate = 1e9 / frequency;
                return time.count() / long long(rate);
            }

        public:
            Impl(double frequency) : start(clock::now()), updates(0), frequency(frequency) { }

            bool update() {
                if (updates < requiredNumberOfUpdates()) {
                    updates++;
                    return true;
                } else {
                    return false;
                }
            }

            double period() {
                return 1.0 / frequency;
            }
        };

        UpdateTimer::UpdateTimer(float frequency) {
            impl = new Impl(frequency);
        }

        UpdateTimer::~UpdateTimer() {
            delete impl;
        }

        bool UpdateTimer::update() {
            return impl->update();
        }

        float UpdateTimer::period() {
            return (float)impl->period();
        }
    }
}