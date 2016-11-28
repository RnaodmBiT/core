#pragma once
#include <functional>
#include <vector>
#include <algorithm>

namespace tk {
    namespace core {

        template <class ...Args>
        class Event;

        template <class ...Args>
        class Delegate {
            Event<Args...>* parent;
            friend class Event<Args...>;
        public:
            ~Delegate() {
                parent->remove(*this);
            }

            std::function<void(Args...)> event;
        };


        template <class ...Args>
        class Event {
            std::vector<Delegate<Args...>*> clients, removeQueue, attachQueue;

            void removeDelegates() {
                for (auto ptr : removeQueue) {
                    clients.erase(std::remove(clients.begin(), clients.end(), ptr), clients.end());
                }
                removeQueue.clear();
            }

            void attachDelegates() {
                for (auto ptr : attachQueue) {
                    clients.push_back(ptr);
                }
                attachQueue.clear();
            }

        public:
            void attach(Delegate<Args...>& client) {
                client.parent = this;
                attachQueue.push_back(&client);
            }

            void remove(Delegate<Args...>& client) {
                removeQueue.push_back(&client);
            }

            void call(const Args&... args) {
                attachDelegates();
                removeDelegates();
                for (auto client : clients) {
                    client->event(args...);
                }
            }

            void operator()(const Args&... args) {
                call(args...);
            }
        };
    }
}
