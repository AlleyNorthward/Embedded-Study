#ifndef _DEBUGGING_HPP
#define _DEBUGGING_HPP

#include "setup_debug.hpp"

class Debug: public SetUpDebug{
public:
    inline Debug():SetUpDebug(){};
    void init();
    void run();
};

#endif
