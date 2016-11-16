#pragma once
#include "resource.hpp"

namespace tk {
    namespace core {

        class State {
            State* nextState;
        protected:
            void setNextState(State* next) {
                nextState = next;
            }
        public:
            State() : nextState(nullptr) { }
            virtual void create(ResourceCollection& resources) { };
            virtual void shutdown() { };
            virtual void draw() { };

            virtual State* update() {
                return nextState;
            }
        };

    }
}
