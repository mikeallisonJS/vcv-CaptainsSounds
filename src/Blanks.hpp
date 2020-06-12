#pragma once
#include "CSModule.hpp"

namespace captainssounds {
    struct BlankModule : CSModule {
        BlankModule() { config(0, 0, 0); }
    };

    struct Blank901 : BlankModule {};
    struct Blank902 : BlankModule {};
    struct Blank904 : BlankModule {};
    struct Blank908 : BlankModule {};
}  // namespace captainssounds

extern Model* modelBlank901;
extern Model* modelBlank902;
extern Model* modelBlank904;
extern Model* modelBlank908;