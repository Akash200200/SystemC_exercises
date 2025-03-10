#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO
template<unsigned int N = 1, unsigned int M = 1, unsigned int L = 0>
SC_MODULE(transition)
{
public:    
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;

    void fire() {
        bool canFire = true;
        // Check for input tokens
        for(int i = 0; i < in.size(); i++) {
            if (in[i]->testTokens() == 0) {
                canFire = false;
                break;
            }
        }

        // Check for inhibitors
        if (canFire) {
            for(int i = 0; i < inhibitors.size(); i++) {
                if (inhibitors[i]->testTokens() != 0) {
                    canFire = false;
                    break;
                }
            }
        }

        if (canFire) {
            // Remove from in
            for(int i = 0; i < in.size(); i++) {
                in[i]->removeTokens();
            }
            // Add to out
            for(int i = 0; i< out.size(); i++) {
                out[i]->addTokens();
            }
            std::cout << this->name() << ": Fired" << std::endl;
        } else {
            std::cout << this->name() << ": NOT Fired" << std::endl;  
        }
        //std::cout << this->name() << ": testing" << std::endl;  
    }

    SC_CTOR (transition) : in("in"), out("out")
    {
        sensitive << in << out;
        //dont_initialize();
    }

};

#endif // TRANSITION_H
