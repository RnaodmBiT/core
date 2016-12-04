#pragma once
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <array>

namespace tk {
    namespace core {
        typedef std::vector<unsigned char> Blob;

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

        template <> void serialize(Blob& bl, const unsigned char& i);

        template <> void serialize(Blob& bl, const unsigned short& i);

        template <> void serialize(Blob& bl, const unsigned int& i);

        template <> void serialize(Blob& bl, const unsigned long long& i);

        template <> void serialize(Blob& bl, const char& i);

        template <> void serialize(Blob& bl, const short& i);

        template <> void serialize(Blob& bl, const int& i);

        template <> void serialize(Blob& bl, const long long& i);

        template <> void serialize(Blob& bl, const float& f);

        template <> void serialize(Blob& b, const std::string& str);


        template <> void deserialize(Blob::const_iterator& it, unsigned char& o);

        template <> void deserialize(Blob::const_iterator& it, unsigned short& o);

        template <> void deserialize(Blob::const_iterator& it, unsigned int& o);

        template <> void deserialize(Blob::const_iterator& it, unsigned long long& o);

        template <> void deserialize(Blob::const_iterator& it, char& o);

        template <> void deserialize(Blob::const_iterator& it, short& o);

        template <> void deserialize(Blob::const_iterator& it, int& o);

        template <> void deserialize(Blob::const_iterator& it, long long& o);

        template <> void deserialize(Blob::const_iterator& it, float& o);

        template <> void deserialize(Blob::const_iterator& it, std::string& str);

        
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
