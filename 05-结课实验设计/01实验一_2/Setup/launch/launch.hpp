#ifndef _LAUNCH_HPP
#define _LAUNCH_HPP

#include "setup.hpp"

class App: public SetUp{
public:
    inline App():SetUp(){};
    void init();
    void run();
};

#endif
