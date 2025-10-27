#include "static_manager.hpp"

BEEP* StaticBuilder::beep[] = {0};
LED* StaticBuilder::led[2] = {0};
KEY* StaticBuilder::key[4] = {0};

WDG_* StaticBuilder::wdg = 0;

