#include <systemc.h>
//#include <iostream>
//#include <queue>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO
SC_MODULE(toplevel)
{
public:
    subnet s1, s2;
    placeChannel<1,1> IDLE;
    
    SC_CTOR (toplevel) : s1("s1"), s2("s2"), IDLE(2)       // Initialize channels. P1 needs a token so can be fired
    {   
        s1.ACT.in.bind(IDLE);
        s2.ACT.in.bind(IDLE);

        s1.PRE.out.bind(IDLE);
        s2.PRE.out.bind(IDLE);

        SC_THREAD (process);
        //dont_initialize();
    }

private:
    void process()
    {
        while (true)
        {
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.RD.fire();
            wait(10, SC_NS);
            s1.WR.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s2.PRE.fire();
            wait(10, SC_NS);
            sc_stop();
        }
    }  
};

int sc_main(int, char**)
{
    toplevel t("t");

    sc_start();
    return 0;
}
