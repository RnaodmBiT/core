#include <serialize.hpp>

namespace tk {
    namespace core {

        void convert<unsigned char>::serialize(Blob& bl, const unsigned char& i) {
            bl.push_back(i);
        }

        void convert<unsigned char>::deserialize(Blob::const_iterator& it, unsigned char& o) {
            o = *(it++);
        }

        void convert<unsigned short>::serialize(Blob& bl, const unsigned short& i) {
            unsigned char a = i & 0xFF, b = (i >> 8) & 0xFF;
            tk::core::serialize(bl, a, b);
        }

        void convert<unsigned short>::deserialize(Blob::const_iterator& it, unsigned short& o) {
            unsigned char a, b;
            tk::core::deserialize(it, a, b);
            o = ((unsigned short)b << 8) | a;
        }

        void convert<unsigned int>::serialize(Blob& bl, const unsigned int& i) {
            unsigned short a = i & 0xFFFF, b = (i >> 16) & 0xFFFF;
            tk::core::serialize(bl, a, b);
        }

        void convert<unsigned int>::deserialize(Blob::const_iterator& it, unsigned int& o) {
            unsigned short a, b;
            tk::core::deserialize(it, a, b);
            o = ((unsigned int)b << 16) | a;
        }

        void convert<unsigned long long>::serialize(Blob& bl, const unsigned long long& i) {
            unsigned int a = i & 0xFFFFFFFF, b = (i >> 32) & 0xFFFFFFFF;
            tk::core::serialize(bl, a, b);
        }

        void convert<unsigned long long>::deserialize(Blob::const_iterator& it, unsigned long long& o) {
            unsigned int a, b;
            tk::core::deserialize(it, a, b);
            o = ((unsigned long long)b << 32) | a;
        }

        void convert<char>::serialize(Blob& bl, const char& i) {
            tk::core::serialize(bl, *(unsigned char*)&i);
        }

        void convert<char>::deserialize(Blob::const_iterator& it, char& o) {
            unsigned char v;
            tk::core::deserialize(it, v);
            o = *(char*)&v;
        }

        void convert<short>::serialize(Blob& bl, const short& i) {
            tk::core::serialize(bl, *(unsigned short*)&i);
        }

        void convert<short>::deserialize(Blob::const_iterator& it, short& o) {
            unsigned short v;
            tk::core::deserialize(it, v);
            v = *(short*)&v;
        }

        void convert<int>::serialize(Blob& bl, const int& i) {
            tk::core::serialize(bl, *(unsigned int*)&i);
        }

        void convert<int>::deserialize(Blob::const_iterator& it, int& o) {
            unsigned int v;
            tk::core::deserialize(it, v);
            o = *(int*)&v;
        }

        void convert<long long>::serialize(Blob& bl, const long long& i) {
            tk::core::serialize(bl, *(unsigned long long*)&i);
        }

        void convert<long long>::deserialize(Blob::const_iterator& it, long long& o) {
            unsigned long long v;
            tk::core::deserialize(it, v);
            o = *(long long*)&v;
        }

        void convert<float>::serialize(Blob& bl, const float& f) {
            tk::core::serialize(bl, *(unsigned int*)&f);
        }

        void convert<float>::deserialize(Blob::const_iterator& it, float& o) {
            unsigned int v;
            tk::core::deserialize(it, v);
            o = *(float*)&v;
        }

        void convert<std::string>::serialize(Blob& b, const std::string& str) {
            unsigned short size = (unsigned short)str.size();
            tk::core::serialize(b, size);
            for (int i = 0; i < str.size(); ++i) {
                tk::core::serialize(b, str[i]);
            }
        }

        void convert<std::string>::deserialize(Blob::const_iterator& it, std::string& str) {
            unsigned short size;
            tk::core::deserialize(it, size);
            str.resize(size);
            for (int i = 0; i < str.size(); ++i) {
                tk::core::deserialize(it, str[i]);
            }
        }
    }
}
