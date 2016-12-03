#pragma once
#include <vector>
#include <memory>
#include <string>

namespace tk {
    namespace core {

        template <class T>
        class Node : public T {
        protected:
            std::string name;
            std::vector<Node*> children;
        public:
            Node(const std::string& name) : name(name) { } 

            void addChild(Node* child) {
                children.emplace_back(child);
            }

            Node* findChild(const std::string& name) {
                for (auto& child : children) {
                    if (child->name == name) {
                        return child.get();
                    }
                }

                for (auto& child : children) {
                    Node* c = child->findChild(name);
                    if (c) {
                        return c;
                    }
                }

                return nullptr;
            }

            void removeChild(Node* child) {
                for (auto i = children.begin(); i != children.end();) {
                    if (*i == child) {
                        i = children.erase(i);
                    } else {
                        ++i;
                    }
                }
            }
        };

    }
}

