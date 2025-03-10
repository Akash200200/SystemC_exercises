#include <iostream>

#include "state_machine.h"

// TODO

void stateMachine::process()
{   
    char in_char = input.read();

    //std::cout << "Current char is: " << in_char << std::endl;

    switch (currentState) 
    {
        //default:
        case Start:
            if (in_char == 'G') {
                currentState = G;
            } else {    // A || C || T
                currentState = Start;
            }
            // No output
            break;

        case G:
            if (in_char == 'A') {
                currentState = GA;
            } else if (in_char == 'G') {
                currentState = G;   // Stay in same state
            } else  {   // C || T
                currentState = Start;
            }
            // No output
            // Update init pos
            init_pos = cur_pos;
            break;

        case GA:
            if (in_char == 'A') {
                currentState = GAA;
            } else if (in_char == 'G') {
                currentState = G;   // Go back one state
            } else  {   // C || T
                currentState = Start;
            }
            // No output
            break;

        case GAA:
            if (in_char == 'G') {
                currentState = GAAG;  // Advance in this state 
            } else if (in_char == 'A') {
                currentState = GAA;   // TASK3: Stay in this state (only change in the FSM diagram)
            } else  {   // A || C || T
                currentState = Start;
            }
            // No output
            break;

        case GAAG:
            if (in_char == 'G') {
                currentState = G;   // Start new sequence
            } else  {   // A || C || T
                currentState = Start;
            }
            // Output
            int len = cur_pos - init_pos + 1;
            
            std::cout << sc_time_stamp().to_default_time_units() << " : Sequence G";
            
            for (int i = 2; i < len; i++)
                std::cout << "A";
            
            std::cout << "G found at position (" << init_pos << "," << cur_pos << ")" << std::endl;
            break;
    }
    cur_pos++;
}