#pragma once
#include <linkage.hpp>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <array>
#include <blob.hpp>

namespace tk {
    namespace core {

        template <class T>
        struct convert {
            void serialize(Blob& blob, T const& value);
            void deserialize(Blob::const_iterator& it, T& value);
        };

#define CONVERT_TYPE(type)  template <> struct TK_CORE convert<type> { \
                                void serialize(Blob& blob, type const& value); \
                                void deserialize(Blob::const_iterator& it, type& value); \
                            };

        template <class T>
        void serialize(Blob& b, T const& value) {
            convert<T>().serialize(b, value);
        }

        template <class T>
        void deserialize(Blob::const_iterator& it, T& value) {
            convert<T>().deserialize(it, value);
        }

        CONVERT_TYPE(unsigned char);
        CONVERT_TYPE(unsigned short);
        CONVERT_TYPE(unsigned int);
        CONVERT_TYPE(unsigned long long);

        CONVERT_TYPE(bool);

        CONVERT_TYPE(char);
        CONVERT_TYPE(short);
        CONVERT_TYPE(int);
        CONVERT_TYPE(long long);

        CONVERT_TYPE(float);
        CONVERT_TYPE(double);

        CONVERT_TYPE(std::string);

        template <class T, class U, class ...Us>
        void serialize(Blob& b, const T& t, const U& u, const Us&... us) {
            serialize(b, t);
            serialize(b, u, us...);
        }

        template <class T, class U, class ...Us>
        void deserialize(Blob::const_iterator& it, T& t, U& u, Us&... us) {
            deserialize(it, t);
            deserialize(it, u, us...);
        }


        template <class T>
        void serialize(Blob& b, const std::vector<T>& list) {
            serialize(b, (unsigned int)list.size());
            for (const T& t : list) {
                serialize(b, t);
            }
        }


        template <class T>
        void deserialize(Blob::const_iterator& it, std::vector<T>& list) {
            unsigned int size;
            deserialize(it, size);
            list.resize(size);
            for (unsigned int i = 0; i < size; ++i) {
                deserialize(it, list[i]);
            }
        }

        /*
        template <class K, class V>
        void serialize(Blob& b, const std::unordered_map<K, V>& map) {
            serialize(b, map.size());
            for (auto& t : map) {
                serialize(b, t.first, t.second);
            }
        }


        template <class K, class V>
        void deserialize(Blob::iterator& it, std::unordered_map<K, V>& map) {
            std::size_t size;
            deserialize(it, size);
            for (unsigned int i = 0; i < size; ++i) {
                K key;
                V value;
                deserialize(it, key, value);
                map[key] = value;
            }
        }

        */
        template <class T, std::size_t N>
        void serialize(Blob& b, const std::array<T, N>& array) {
            for (std::size_t i = 0; i < N; ++i) {
                serialize(b, array[i]);
            }
        }


        template <class T, std::size_t N>
        void deserialize(Blob::const_iterator& it, std::array<T, N>& array) {
            for (std::size_t i = 0; i < N; ++i) {
                deserialize(it, array[i]);
            }
        }

    }
}
