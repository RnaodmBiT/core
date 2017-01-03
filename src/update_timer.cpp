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
            double timeStep;

            long long requiredNumberOfUpdates() {
                std::chrono::nanoseconds time = clock::now() - start;
                double rate = 1e9 * timeStep;
                return time.count() / (long long)(rate);
            }

        public:
            Impl(double frequency) : start(clock::now()), updates(0), timeStep(1 / frequency) { }

            bool update() {
                if (updates < requiredNumberOfUpdates()) {
                    updates++;
                    return true;
                } else {
                    return false;
                }
            }

            double period() {
                return timeStep;
            }

            double progress() {
                std::chrono::nanoseconds time = clock::now() - start;
                double now = (double)time.count() / 1e9;
                return std::fmod(now, timeStep);
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

        float UpdateTimer::progress() {
            return (float)impl->progress();
        }
    }
}
