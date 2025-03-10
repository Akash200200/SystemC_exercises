#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// TODO
class placeInterface : public sc_interface{
public:
    // Virtual functions
    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;
    virtual bool testTokens() = 0;
};

// Place Channel:
// TODO
template<unsigned int Win = 1, unsigned int Wout = 1>
class placeChannel : public placeInterface {
private:
    unsigned int tokens;
    
public:
    placeChannel(unsigned int numTokens = 0) : tokens(numTokens) {}

    void addTokens() {
        tokens = tokens + Win;
    }

    void removeTokens() {
        tokens = tokens - Wout;
    }

    bool testTokens() {
        return tokens >= Wout ? 1 : 0;
    }
};

#endif // PLACE_H
