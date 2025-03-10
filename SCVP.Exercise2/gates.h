#ifndef GATES_H
#define GATES_H

#include <systemc.h>


SC_MODULE (orr)
{
    sc_in<bool>  A;
    sc_in<bool>  B;
    sc_out<bool> Z;

    void do_or()
    {
        Z.write((A.read() || B.read()));
    }

    SC_CTOR (orr) : A("A"), B("B"), Z("Z")
    {
        SC_METHOD (do_or);
        sensitive << A << B;
    }
};

SC_MODULE (andd)
{
    sc_in<bool>  A;
    sc_in<bool>  B;
    sc_out<bool> Z;

    void do_and()
    {
        Z.write((A.read() && B.read()));
    }

    SC_CTOR (andd) : A("A"), B("B"), Z("Z")
    {
        SC_METHOD (do_and);
        sensitive << A << B;
    }
};

SC_MODULE (nott)
{
    sc_in<bool>  A;
    sc_out<bool> Z;

    void do_not()
    {
        Z.write(!A.read());
    }

    SC_CTOR (nott) : A("A"), Z("Z")
    {
        SC_METHOD (do_not);
        sensitive << A;
    }
};

#endif
