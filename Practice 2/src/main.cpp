#include <systemc>
#include "MovingAverage.h"

using namespace sc_core;

SC_MODULE(Testbench)
{
    sc_signal<unsigned int> xn;
    sc_signal<unsigned int> yn;
    sc_clock clk;
    sc_signal<bool> rst;

    MovingAverage movAvg;

    void process()
    {
        rst = true;
        wait(clk.negedge_event());
        rst = false;
        
        sc_assert(yn == 0);

        xn = 1;
        wait(1, SC_NS);
        sc_assert(yn == 0);
        wait(clk.negedge_event());

        xn = 2;
        wait(1, SC_NS);
        sc_assert(yn == 0);
        wait(clk.negedge_event());

        xn = 3;
        wait(1, SC_NS);
        sc_assert(yn == 1);
        wait(clk.negedge_event());

        xn = 4;
        wait(1, SC_NS);
        sc_assert(yn == 2);
        wait(clk.negedge_event());

        xn = 5;
        wait(1, SC_NS);
        sc_assert(yn == 3);
        wait(clk.negedge_event());

        xn = 6;
        wait(1, SC_NS);
        sc_assert(yn == 4);
        wait(clk.negedge_event());

        xn = 7;
        wait(1, SC_NS);
        sc_assert(yn == 5);
        wait(clk.negedge_event());

        xn = 8;
        wait(1, SC_NS);
        sc_assert(yn == 6);
        wait(clk.negedge_event());

        rst = true;
        wait(1, SC_NS);
        sc_assert(yn == 2);

        std::cout << "Simulation successful!" << std::endl;

        sc_stop();
    }

    SC_CTOR(Testbench) : xn("xn", 0), yn("yn", 0), clk("clk", 10, SC_NS), rst("rst", false), movAvg("movAvg")
    {
        SC_THREAD(process);

        movAvg.clk.bind(clk);
        movAvg.rst.bind(rst);
        movAvg.xn.bind(xn);
        movAvg.yn.bind(yn);
    }
};

int sc_main(int, char **)
{
    Testbench t("t");

    sc_set_stop_mode(SC_STOP_FINISH_DELTA);
    sc_start();

    return 0;
}
