#include "random.hpp"
#include <random>

namespace tk {
    namespace core {

        static std::random_device device;
        static std::mt19937 generator(device());

        float random(float min, float max) {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(generator);
        }

    }
}
