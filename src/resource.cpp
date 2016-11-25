#include <resource.hpp>
#include <unordered_map>
#include <memory>
#include <log.hpp>
#include <utility.hpp>

namespace tk {
    namespace core {

        class ResourceCollection::Impl {
            std::unordered_map<std::string, std::unique_ptr<IResource>> resources;

        public:
            
            IResource* getResource(const std::string& key) {
                if (resources.count(key) == 0) {
                    return nullptr;
                }
                return resources[key].get();
            }

            void cacheResource(const std::string& key, IResource* resource) {
                resources[key].reset(resource);
            }
        };


        ResourceCollection::ResourceCollection() {
            impl = new Impl();
        }

        ResourceCollection::~ResourceCollection() {
            delete impl;
        }


        IResource* ResourceCollection::getResource(const std::string& key) const {
            return impl->getResource(key);
        }

        void ResourceCollection::cacheResource(const std::string& key, IResource* resource) {
            impl->cacheResource(key, resource);
        }

    }
}
