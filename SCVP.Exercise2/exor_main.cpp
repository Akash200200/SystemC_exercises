#include <systemc.h>

#include "stim.h"
#include "exor.h"
//#include "gates.h"
#include "mon.h"

int sc_main(int, char**)
{
    sc_signal<bool> sigA, sigB, sigZ;
    sc_clock clk("clk", 10, SC_NS, 0.5);

    stim Stim1("Stimulus");
    Stim1.A(sigA);
    Stim1.B(sigB);
    Stim1.Clk(clk);

    exor DUT("exor");
    DUT.A(sigA);
    DUT.B(sigB);
    DUT.Z(sigZ);

    Monitor mon("Monitor");
    mon.A(sigA);
    mon.B(sigB);
    mon.Z(sigZ);
    mon.Clk(clk);

    // [Simon]: Setup waveform tracing
    sc_trace_file *wf = sc_create_vcd_trace_file("trace");
    sc_trace(wf, sigA, "sigA");
    sc_trace(wf, sigB, "sigB");
    sc_trace(wf, sigZ, "sigZ"); 
    sc_trace(wf, clk, "clk"); 

    sc_start();  // run forever

    // [Simon]: Close trace file
    sc_close_vcd_trace_file(wf);

    return 0;
}
