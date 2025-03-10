#pragma once

// Simon Blanco Ortiz - 430128
#include <systemc.h>

SC_MODULE (MovingAverage)
{

    private:
    sc_signal <unsigned int> Q1, Q2, Q3;

    public:
    sc_in<unsigned int> xn;
    sc_out<unsigned int> yn;
    sc_in <bool> clk;
    sc_in <bool> rst;


    void ma_proc() {
        if (rst.read()) {
            // set everything to 0
            Q1 = 0;
            Q2 = 0;
            Q3 = 0;

        } else if (clk.read()){
            Q1 = xn;
            Q2 = Q1;
            Q3 = Q2;
        }

        //std::cout << sc_time_stamp().to_default_time_units() << ": xn: " << xn << "\t Q1: " << Q1 << "\t Q2: " << Q3 << "\t Q3: " << Q3 << "\t yn: " << yn << std::endl;
    }

    void comb_proc() {
        yn = (xn + Q1 + Q2 + Q3) / 4;
    }

    SC_CTOR (MovingAverage) : xn("xn"), yn("yn"), clk("clk"), rst("rst")
    {
        SC_METHOD (ma_proc);
        sensitive << clk << rst;

        SC_METHOD (comb_proc);
        sensitive << xn << Q1 << Q2 << Q3;
    }
};
