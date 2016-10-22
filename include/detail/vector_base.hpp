#pragma once
#include <array>


namespace tk {
    namespace core {
        namespace detail {

            template <class T, int N>
            class VectorData {
            public:
                std::array<T, N> data;
            };


            // Common 3D vector specializations
            template <class T>
            class VectorData<T, 2> {
            public:
                union {
                    std::array<T, 2> data;
                    struct { T x, y; };
                };
            };


            template <class T>
            class VectorData<T, 3> {
            public:
                union {
                    std::array<T, 3> data;
                    struct { T x, y, z; };
                };
            };


            template <class T>
            class VectorData<T, 4> {
            public:
                union {
                    std::array<T, 4> data;
                    struct { T x, y, z, w; };
                };
            };

        }
    }
}