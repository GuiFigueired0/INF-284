#pragma once

#include "tsp_p1.h"

class GreedyTSP : public LocalSearchTSP {
public:
    GreedyTSP(std::string path, int n, int t, double p, double l);
    
    ll greedyInitialization(bool bothSides = true);
};