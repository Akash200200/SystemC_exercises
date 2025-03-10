#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

// TODO
SC_MODULE(stateMachine)
{
public:
    sc_in<char> input;
    sc_in<bool> clk;


    enum base {Start, G, GA, GAA, GAAG};
    enum base currentState;
    int cur_pos;
    int init_pos;

    void process();

    SC_CTOR (stateMachine) : input("Input"), clk("Clk")
    {
        currentState = Start;   // Intialize state
        cur_pos = 1;

        SC_METHOD (process);
        sensitive << clk.pos();
        //dont_initialize();
    }
};
#endif // STATE_MACHINE_H


