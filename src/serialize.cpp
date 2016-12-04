#include <serialize.hpp>

namespace tk {
    namespace core {

        template <>
        void serialize(Blob& bl, const unsigned char& i) {
            bl.push_back(i);
        }

        template <>
        void serialize(Blob& bl, const unsigned short& i) {
            unsigned char a = i & 0xFF, b = (i >> 8) & 0xFF;
            serialize(bl, a, b);
        }

        template <>
        void serialize(Blob& bl, const unsigned int& i) {
            unsigned short a = i & 0xFFFF, b = (i >> 16) & 0xFFFF;
            serialize(bl, a, b);
        }

        template <>
        void serialize(Blob& bl, const unsigned long long& i) {
            unsigned int a = i & 0xFFFFFFFF, b = (i >> 32) & 0xFFFFFFFF;
            serialize(bl, a, b);
        }

        template <>
        void serialize(Blob& bl, const char& i) {
            serialize(bl, *(unsigned char*)&i);
        }

        template <>
        void serialize(Blob& bl, const short& i) {
            serialize(bl, *(unsigned short*)&i);
        }

        template <>
        void serialize(Blob& bl, const int& i) {
            serialize(bl, *(unsigned int*)&i);
        }

        template <>
        void serialize(Blob& bl, const long long& i) {
            serialize(bl, *(unsigned long long*)&i);
        }

        template <>
        void serialize(Blob& bl, const float& f) {
            serialize(bl, *(unsigned int*)&f);
        }


        template <>
        void serialize(Blob& b, const std::string& str) {
            unsigned short size = (unsigned short)str.size();
            serialize(b, size);
            for (int i = 0; i < str.size(); ++i) {
                serialize(b, str[i]);
            }
        }


        template <>
        void deserialize(Blob::const_iterator& it, unsigned char& o) {
            o = *(it++);
        }

        template <>
        void deserialize(Blob::const_iterator& it, unsigned short& o) {
            unsigned char a, b;
            deserialize(it, a, b);
            o = ((unsigned short)b << 8) | a;
        }

        template <>
        void deserialize(Blob::const_iterator& it, unsigned int& o) {
            unsigned short a, b;
            deserialize(it, a, b);
            o = ((unsigned int)b << 16) | a;
        }

        template <>
        void deserialize(Blob::const_iterator& it, unsigned long long& o) {
            unsigned int a, b;
            deserialize(it, a, b);
            o = ((unsigned long long)b << 32) | a;
        }

        template <>
        void deserialize(Blob::const_iterator& it, char& o) {
            unsigned char v;
            deserialize(it, v);
            o = *(char*)&v;
        }

        template <>
        void deserialize(Blob::const_iterator& it, short& o) {
            unsigned short v;
            deserialize(it, v);
            v = *(short*)&v;
        }

        template <>
        void deserialize(Blob::const_iterator& it, int& o) {
            unsigned int v;
            deserialize(it, v);
            o = *(int*)&v;
        }

        template <>
        void deserialize(Blob::const_iterator& it, long long& o) {
            unsigned long long v;
            deserialize(it, v);
            o = *(long long*)&v;
        }

        template <>
        void deserialize(Blob::const_iterator& it, float& o) {
            unsigned int v;
            deserialize(it, v);
            o = *(float*)&v;
        }

        template <>
        void deserialize(Blob::const_iterator& it, std::string& str) {
            unsigned short size;
            deserialize(it, size);
            str.resize(size);
            for (int i = 0; i < str.size(); ++i) {
                deserialize(it, str[i]);
            }
        }
    }
}
