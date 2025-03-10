#pragma once

// Simon Blanco Ortiz - 430128
#include <iostream>
#include <systemc.h>
#include <queue>

using namespace std;

//template <class unsigned int>
class SimpleFifoInterface : public sc_interface
{
    public:
    virtual unsigned int read() = 0;
    virtual void write(unsigned int) = 0;
    // Just for Debug
    virtual void printFIFO()
    {
        cout << "Warning: Debug Function Not Implemented" << endl;
    }
};

//template <class T>
class SimpleFifo : public SimpleFifoInterface
{
    private:
    std::queue<unsigned int> fifo;
    sc_event writtenEvent;
    sc_event readEvent;
    unsigned int maxSize;

    public:
    SimpleFifo(unsigned int size=16) : maxSize(size)
    {
    }

    unsigned int read()
    {
        if(fifo.empty() == true)
        {
            std::cout << "Wait for Write" << std::endl;
            wait(writtenEvent);
        }
        unsigned int val = fifo.front();
        fifo.pop();
        readEvent.notify(SC_ZERO_TIME);
        return val;
    }

    void write(unsigned int d)
    {
        if(fifo.size() == maxSize)
        {
            std::cout << "Wait for Read" << std::endl;
            wait(readEvent);
        }
        fifo.push(d);
        writtenEvent.notify(SC_ZERO_TIME);
    }

    void printFIFO()
    {
        unsigned int n = fifo.size();

        std::cout << "SimpleFifo (" << maxSize << ") " << "[";
        for(unsigned int i = 0; i < n; i++) {
            std::cout << "█";
        }
        for(unsigned int i = 0; i < maxSize-n; i++) {
            std::cout << " ";
        }
        std::cout << "]" << std::endl;
        std::cout.flush();
    }
};

SC_MODULE(PRODUCER)
{
    sc_port< SimpleFifoInterface > master;

    SC_CTOR(PRODUCER)
    {
        SC_THREAD(process);
    }

    void process()
    {
        while(true)
        {
            wait(1,SC_NS);
            master->write(10);
            std::cout << "@" << sc_time_stamp() << " Write: 10 ";
            master->printFIFO();
        }
    }
};

SC_MODULE(CONSUMER)
{
    sc_port< SimpleFifoInterface > slave;

    SC_CTOR(CONSUMER)
    {
        SC_THREAD(process);
        sensitive << slave;
    }

    void process()
    {
        while(true)
        {
            wait(4,SC_NS);
            std::cout << "@" << sc_time_stamp() << " Read : "
                      << slave->read() << " ";
            slave->printFIFO();
        }
    }
};