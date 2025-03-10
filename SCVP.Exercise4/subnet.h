#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"

// Subnet:
// TODO
SC_MODULE(subnet)
{
public:
    transition<1,1,1> ACT;
    transition<1,1,0> RD;
    transition<1,1,0> PRE;
    transition<1,1,0> WR;


    placeChannel<1,1> ACTIVE;
    
    SC_CTOR (subnet) : ACT("ACT"), RD("RD"), PRE("PRE"), WR("WR"), ACTIVE(0)       // Initialize channels. P1 needs a token so can be fired
    {   
        //ACT.in.bind(IDLE);
        ACT.out.bind(ACTIVE);
        ACT.inhibitors.bind(ACTIVE);

        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);

        PRE.in.bind(ACTIVE);
        //PRE.out.bind(IDLE);

        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);


        //sensitive << ACT << RD << PRE << WR;
        //dont_initialize();
    }
};

#endif // SUBNET_H
