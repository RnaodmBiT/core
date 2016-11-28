#pragma once
#include "resource.hpp"

namespace tk {
    namespace core {

        template <class T>
        class State {
            State<T>* nextState;
        protected:
            T& global;
            void setNextState(State<T>* next) {
                nextState = next;
            }
        public:
            State(T& init) : nextState(nullptr), global(init) { }
            virtual ~State() { }
            virtual void shutdown() { };
            virtual void draw() { };

            virtual State<T>* update(float dt) {
                return nextState;
            }
        };

    }
}
