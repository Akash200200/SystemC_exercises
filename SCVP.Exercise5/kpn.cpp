#include <unistd.h>
#include <systemc.h>

#include "kpn.h"

// ADD THINGS HERE
void kpn::add()
{
    while(true){
        b.write(a.read() + c.read());
    }
}

void kpn::split()
{
    while(true){
        unsigned int temp = b.read();
        a.write(temp);
        d.write(temp);
        e = temp;

        printOutput();
        cnt++;
        if (cnt >= 10) {
            sc_stop();
        }
    }
}

void kpn::delay()
{
    while(true){
        c.write(d.read());
    }
}

void kpn::printOutput()
{
     std::cout << "e: " << e << std::endl;  
}