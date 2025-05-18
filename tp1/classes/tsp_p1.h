#pragma once

#include "tsp.h"

class LocalSearchTSP : public TSP {
public:
    LocalSearchTSP(std::string path, int n, int t, double p, double l);
    
    ll solve() override;
};