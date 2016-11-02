#pragma once
#include <string>

namespace tk {
    namespace core {

        class IResource {
        public:
            virtual ~IResource() { }
        };

        class ResourceCollection {
            class Impl;
            Impl* impl;

            IResource* getResource(const std::string& key);
            void cacheResource(const std::string& key, IResource* resource);

        public:
            ResourceCollection();
            ~ResourceCollection();

            template <class T, class ...Args>
            T* load(const std::string& key, const Args&... args) {
                if (get<T>(key) == nullptr) {
                    cacheResource(key, T::loadFromFile(args...));
                }
                return get<T>(key);
            }

            template <class T>
            T* get(const std::string& key) {
                return dynamic_cast<T*>(getResource(key));
            }
        };

    }
}
