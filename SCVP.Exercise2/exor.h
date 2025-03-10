#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>
#include "nand.h"

// TODO: Insert your code here
SC_MODULE (exor)
{
    sc_in<bool>  A;
    sc_in<bool>  B;
    sc_out<bool> Z;

    sc_signal<bool> h1;
    sc_signal<bool> h2;
    sc_signal<bool> h3;

    nand a, b, c, d;

    SC_CTOR (exor) : a("a"), b("b"), c("c"), d("d"), A("A"), B("B"), Z("Z"), h1("h1"), h2("h2"), h3("h3")
    {
        a.A.bind(A);
        a.B.bind(B);
        a.Z.bind(h1);

        b.A.bind(h1);
        b.B.bind(B);
        b.Z.bind(h2);

        c.A.bind(A);
        c.B.bind(h1);
        c.Z.bind(h3);
        
        d.A.bind(h3);
        d.B.bind(h2);
        d.Z.bind(Z);


        sensitive << A << B;
    }
};

#endif // EXOR_H
