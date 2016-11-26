#pragma once
#include "resource.hpp"

namespace tk {
    namespace core {

        template <class T>
        class State {
            State<T>* nextState;
        protected:
            void setNextState(State<T>* next) {
                nextState = next;
            }
        public:
            State() : nextState(nullptr) { }
            virtual ~State() { }
            virtual void create(T& init) { };
            virtual void shutdown() { };
            virtual void draw() { };

            virtual State<T>* update() {
                return nextState;
            }
        };

    }
}
