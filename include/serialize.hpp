#pragma once
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <array>

namespace tk {
    namespace core {
        typedef std::vector<uint8_t> Blob;

        template <class T>
        void serialize(Blob& b, const T& obj);

        template <class T>
        void deserialize(Blob::const_iterator& it, T& o);

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

        static void serialize(Blob& bl, const uint8_t& i) {
            bl.push_back(i);
        }

        static void serialize(Blob& bl, const uint16_t& i) {
            uint8_t a = i & 0xFF, b = (i >> 8) & 0xFF;
            serialize(bl, a, b);
        }

        static void serialize(Blob& bl, const uint32_t& i) {
            uint16_t a = i & 0xFFFF, b = (i >> 16) & 0xFFFF;
            serialize(bl, a, b);
        }

        static void serialize(Blob& bl, const uint64_t& i) {
            uint32_t a = i & 0xFFFFFFFF, b = (i >> 32) & 0xFFFFFFFF;
            serialize(bl, a, b);
        }

        static void serialize(Blob& bl, const char& i) {
            serialize(bl, *(uint8_t*)&i);
        }

        static void serialize(Blob& bl, const int16_t& i) {
            serialize(bl, *(uint16_t*)&i);
        }

        static void serialize(Blob& bl, const int32_t& i) {
            serialize(bl, *(uint32_t*)&i);
        }

        static void serialize(Blob& bl, const int64_t& i) {
            serialize(bl, *(uint64_t*)&i);
        }

        static void serialize(Blob& bl, const float& f) {
            serialize(bl, *(uint32_t*)&f);
        }


        static void serialize(Blob& b, const std::string& str) {
            uint16_t size = (uint16_t)str.size();
            serialize(b, size);
            for (int i = 0; i < str.size(); ++i) {
                serialize(b, str[i]);
            }
        }


        static void deserialize(Blob::const_iterator& it, uint8_t& o) {
            o = *(it++);
        }

        static void deserialize(Blob::const_iterator& it, uint16_t& o) {
            uint8_t a, b;
            deserialize(it, a, b);
            o = ((uint16_t)b << 8) | a;
        }


        static void deserialize(Blob::const_iterator& it, uint32_t& o) {
            uint16_t a, b;
            deserialize(it, a, b);
            o = ((uint32_t)b << 16) | a;
        }

        static void deserialize(Blob::const_iterator& it, uint64_t& o) {
            uint32_t a, b;
            deserialize(it, a, b);
            o = ((uint64_t)b << 32) | a;
        }

        static void deserialize(Blob::const_iterator& it, char& o) {
            uint8_t v;
            deserialize(it, v);
            o = *(char*)&v;
        }

        static void deserialize(Blob::const_iterator& it, int16_t& o) {
            uint16_t v;
            deserialize(it, v);
            v = *(int16_t*)&v;
        }

        static void deserialize(Blob::const_iterator& it, int32_t& o) {
            uint32_t v;
            deserialize(it, v);
            o = *(int32_t*)&v;
        }

        static void deserialize(Blob::const_iterator& it, int64_t& o) {
            uint64_t v;
            deserialize(it, v);
            o = *(int64_t*)&v;
        }

        static void deserialize(Blob::const_iterator& it, float& o) {
            uint32_t v;
            deserialize(it, v);
            o = *(float*)&v;
        }

        static void deserialize(Blob::const_iterator& it, std::string& str) {
            uint16_t size;
            deserialize(it, size);
            str.resize(size);
            for (int i = 0; i < str.size(); ++i) {
                deserialize(it, str[i]);
            }
        }

        
        template <class T>
        void serialize(Blob& b, const std::vector<T>& list) {
            serialize(b, (uint32_t)list.size());
            for (const T& t : list) {
                serialize(b, t);
            }
        }


        template <class T>
        void deserialize(Blob::const_iterator& it, std::vector<T>& list) {
            uint32_t size;
            deserialize(it, size);
            list.resize(size);
            for (uint32_t i = 0; i < size; ++i) {
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
            for (uint32_t i = 0; i < size; ++i) {
                K key;
                V value;
                deserialize(it, key, value);
                map[key] = value;
            }
        }


        template <class T, std::size_t N>
        void serialize(Blob& b, const std::array<T, N>& array) {
            for (std::size_t i = 0; i < N; ++i) {
                serialize(b, array[i]);
            }
        }


        template <class T, std::size_t N>
        void deserialize(Blob::iterator& it, std::array<T, N>& array) {
            for (std::size_t i = 0; i < N; ++i) {
                deserialize(it, array[i]);
            }
        }
        */
    }
}