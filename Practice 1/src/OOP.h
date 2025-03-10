#pragma once

#include <systemc.h>
SC_MODULE (RSLatch)
{
    sc_in<bool>  A;
    sc_in<bool>  B;
    sc_out<bool> D;

    sc_signal<bool> C;

    void process() {
        C.write(A.read() || D.read());
        D.write(C.read() && !(B.read()));
    }

    SC_CTOR (RSLatch) : A("A"), B("B"), C("C"), D("D")
    {
        SC_METHOD (process);
        sensitive << A << B << C << D;
    }
};