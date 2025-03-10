#include <tuple>
#include <systemc>
#include "RSLatch.h"

using namespace sc_core;

SC_MODULE(Testbench)
{
    sc_signal<bool> Asig;
    sc_signal<bool> Bsig;
    sc_signal<bool> Dsig;

    RSLatch rslatch;
    sc_time currentTime;
    unsigned long long currentDelta;

    void waitAndCompare(const sc_time& delay, std::tuple<bool, bool, bool, bool> expected)
    {
        wait(delay);
        const sc_time& time = sc_time_stamp();

        if (time > currentTime)
        {
            currentDelta = sc_delta_count();
            currentTime = time;
        }

        uint64_t delta = sc_delta_count() - currentDelta;

        std::tuple<bool, bool, bool, bool> actual = {rslatch.A.read(), rslatch.B.read(),
                                                     rslatch.C.read(), rslatch.D.read()};

        if (actual != expected)
        {
            std::cout << "Wrong values at " << time << " + " << delta << "δ" << std::endl
            << "\t\t\tA\tB\tC\tD" << std::endl
            << "Expected:\t" << std::get<0>(expected) << "\t" << std::get<1>(expected)
                    << "\t" << std::get<2>(expected) << "\t" << std::get<3>(expected) << std::endl
            << "Actual:\t\t" << std::get<0>(actual) << "\t" << std::get<1>(actual)
                    << "\t" << std::get<2>(actual) << "\t" << std::get<3>(actual) << std::endl;
            SC_REPORT_FATAL("Wrong output", "Simulation stopped");
        }
    }

    void process()
    {
        std::cout << "Initializing A and B with 0" << std::endl;
        Asig.write(false);
        Bsig.write(false);

        waitAndCompare(SC_ZERO_TIME, {false, false, false, false});
        waitAndCompare(SC_ZERO_TIME, {false, false, false, false});
        waitAndCompare(SC_ZERO_TIME, {false, false, false, false});

        wait(10, SC_NS);
        std::cout << "Setting A to 1 at " << sc_time_stamp() << std::endl;
        Asig.write(true);

        waitAndCompare(SC_ZERO_TIME, {true, false, false, false});
        waitAndCompare(SC_ZERO_TIME, {true, false, true, false});
        waitAndCompare(SC_ZERO_TIME, {true, false, true, true});

        wait(10, SC_NS);
        std::cout << "Setting A to 0 at " << sc_time_stamp() << std::endl;
        Asig.write(false);

        waitAndCompare(SC_ZERO_TIME, {false, false, true, true});
        waitAndCompare(SC_ZERO_TIME, {false, false, true, true});
        waitAndCompare(SC_ZERO_TIME, {false, false, true, true});

        wait(10, SC_NS);
        std::cout << "Setting B to 1 at " << sc_time_stamp() << std::endl;
        Bsig.write(true);

        waitAndCompare(SC_ZERO_TIME, {false, true, true, true});
        waitAndCompare(SC_ZERO_TIME, {false, true, true, false});
        waitAndCompare(SC_ZERO_TIME, {false, true, false, false});

        wait(10, SC_NS);
        std::cout << "Setting B to 0 at " << sc_time_stamp() << std::endl;
        Bsig.write(false);

        waitAndCompare(SC_ZERO_TIME, {false, false, false, false});
        waitAndCompare(SC_ZERO_TIME, {false, false, false, false});
        waitAndCompare(SC_ZERO_TIME, {false, false, false, false});

        std::cout << "Simulation successful!" << std::endl;

        sc_stop();
    }

    SC_CTOR(Testbench) : rslatch("rslatch")
    {
        SC_THREAD(process);

        rslatch.A.bind(Asig);
        rslatch.B.bind(Bsig);
        rslatch.D.bind(Dsig);

        currentTime = sc_time_stamp();
        currentDelta = sc_delta_count();
    }
};

int sc_main(int, char **)
{
    Testbench t("t");

    sc_set_stop_mode(SC_STOP_FINISH_DELTA);
    sc_start();

    return 0;
}
