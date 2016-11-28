#pragma once

namespace tk {
    namespace core {
        namespace {
            constexpr float pi = 3.14159265359f;
        }

        static float wrapAngle(float angle) {
            while (angle > pi) {
                angle -= pi * 2;
            }
            while (angle < -pi) {
                angle += pi * 2;
            }
            return angle;
        }

        static float sign(float x) {
            return x > 0.0f ? 1.0f : x < 0.0f ? -1.0f : 0.0f;
        }
    }
}