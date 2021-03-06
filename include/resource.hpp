#pragma once
#include <string>
#include <log.hpp>
#include <utility.hpp>

namespace tk {
    namespace core {

        class TK_CORE IResource {
        public:
            virtual ~IResource() { }
        };

        class TK_CORE ResourceCollection {
            class Impl;
            Impl* impl;

            IResource* getResource(const std::string& key) const;
            void cacheResource(const std::string& key, IResource* resource);

        public:
            ResourceCollection();
            ~ResourceCollection();

            template <class T, class ...Args>
            T* load(const std::string& key, const Args&... args) {
                if (getResource(key) == nullptr) {
                    cacheResource(key, T::loadFromFile(args...));
                }
                return get<T>(key);
            }

            template <class T>
            T* get(const std::string& key) const {
                IResource* ptr = getResource(key);
                tk_warn(ptr, format("Resource '%%' does not exist.", key));
                return dynamic_cast<T*>(ptr);
            }
        };

    }
}
