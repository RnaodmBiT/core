#pragma once
#include <vector>
#include <memory>
#include <string>

namespace tk {
    namespace core {

        template <class I>
        class Node {
        protected:
            std::string name;
            std::vector<std::unique_ptr<I>> children;
        public:
            Node(const std::string& name) : name(name) { } 

            void addChild(I* child) {
                children.emplace_back(child);
            }

            I* findChild(const std::string& name) {
                return nullptr;
            }

            std::unique_ptr<I> removeChild(I* child) {
                return nullptr;
            }
        };

    }
}

