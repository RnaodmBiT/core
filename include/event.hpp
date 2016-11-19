#pragma once
#include <functional>
#include <vector>

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
            std::vector<Delegate<Args...>*> clients;
            std::vector<Delegate<Args...>*> removeQueue;

            void removeDelegates() {
                for (auto ptr : removeQueue) {
                    clients.erase(std::remove(clients.begin(), clients.end(), ptr), clients.end());
                }
            }
        public:
            void attach(Delegate<Args...>& client) {
                client.parent = this;
                clients.push_back(&client);
            }

            void remove(Delegate<Args...>& client) {
                removeQueue.push_back(&client);
            }

            void call(const Args&... args) {
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