#pragma once

#include "tsp.h"
#include <random>

// Constraint: N >= 5 for perturb() to work correctly (get4SortedRandom)
class ILS_TSP : public TSP {
private: 
    std::mt19937 rng;  

protected:
    std::vector<int> m_get4SortedRandom(); // Created by ChatGPT
    bool m_stochasticChange(double oldValue, double newSolution, double temp);
    
    void m_perturb();
    void m_accept(Solution &lastFound, int newSolution, int t, double temp);

public:
    ILS_TSP(std::string path, int n, int t, double p, double l);
    
    ll solve() override;
};