#pragma once
#include <functional>
#include <vector>
#include <algorithm>
#include <unordered_set>

namespace tk {
    namespace core {

        template <class ...Args>
        class Event;

        template <class ...Args>
        class Delegate {
            Event<Args...>* parent;
            friend class Event<Args...>;
        public:
            Delegate() : parent(nullptr) { }
            ~Delegate() {
                if (parent) {
                    parent->remove(*this);
                }
            }

            std::function<void(Args...)> event;
        };


        template <class ...Args>
        class Event {
            std::unordered_set<Delegate<Args...>*> clients, removeQueue, attachQueue;

            void updateDelegates() {
                for (auto ptr : removeQueue) {
                    clients.erase(ptr);
                    ptr->parent = nullptr;
                }
                removeQueue.clear();

                for (auto ptr : attachQueue) {
                    clients.insert(ptr);
                }
                attachQueue.clear();
            }

        public:
            ~Event() {
                for (auto ptr : clients) {
                    ptr->parent = nullptr;
                }

                for (auto ptr : attachQueue) {
                    ptr->parent = nullptr;
                }
            }

            void attach(Delegate<Args...>& client) {
                client.parent = this;
                if (removeQueue.count(&client)) {
                    removeQueue.erase(&client);
                } else {
                    attachQueue.insert(&client);
                }
            }

            template <class T>
            void attach(Delegate<Args...>& client, T func) {
                client.event = func;
                attach(client);
            }

            void remove(Delegate<Args...>& client) {
                if (attachQueue.count(&client)) {
                    attachQueue.erase(&client);
                } else {
                    removeQueue.insert(&client);
                }
            }

            void call(const Args&... args) {
                updateDelegates();
                for (auto client : clients) {
                    if (client->event) {
                        client->event(args...);
                    }
                }
            }

            void operator()(const Args&... args) {
                call(args...);
            }
        };
    }
}
