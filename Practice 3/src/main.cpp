#include <systemc>
#include "SimpleFifo.h"

using namespace sc_core;

SC_MODULE(Testbench)
{
    sc_port<SimpleFifo> writePort;
    sc_port<SimpleFifo> readPort;

    SimpleFifo fifo;

    bool readAllowed, writeAllowed;

    void readProcess()
    {
        unsigned int val;
        wait(1, SC_NS);
        readAllowed = false;
        val = readPort->read();
        sc_assert(readAllowed);
        sc_assert(val == 1);
        sc_assert(sc_time_stamp() == sc_time(2, SC_NS));
        wait(2, SC_NS);
        val = readPort->read();
        writeAllowed = true;
        sc_assert(val == 2);
        wait(1, SC_NS);
        val = readPort->read();
        sc_assert(val == 3);
        val = readPort->read();
        sc_assert(val == 4);
        val = readPort->read();
        sc_assert(val == 5);
        val = readPort->read();
        sc_assert(val == 6);

        std::cout << "Simulation successful!" << std::endl;

        sc_stop();
    }

    void writeProcess()
    {
        wait(2, SC_NS);
        writePort->write(1);
        readAllowed = true;
        wait(1, SC_NS);
        writePort->write(2);
        writePort->write(3);
        writePort->write(4);
        writePort->write(5);
        writeAllowed = false;
        writePort->write(6);
        sc_assert(writeAllowed);
        sc_assert(sc_time_stamp() == sc_time(4, SC_NS));
    }

    SC_CTOR(Testbench) : fifo(4), readAllowed(true), writeAllowed(true)
    {
        writePort.bind(fifo);
        readPort.bind(fifo);

        SC_THREAD(readProcess);
        SC_THREAD(writeProcess);
    }
};

int sc_main(int, char **)
{
    Testbench t("t");

    sc_set_stop_mode(SC_STOP_FINISH_DELTA);
    sc_start();

    return 0;
}
