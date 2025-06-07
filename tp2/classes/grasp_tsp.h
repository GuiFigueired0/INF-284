#pragma once

#include "ils_tsp.h"

class GRASP_TSP : public ILS_TSP {
private:
    double m_alpha;
protected:
    Solution m_pathRelinking(Solution a, Solution &b, int iteration);
    void m_GreedyRandomizedConstruction();
    void m_UpdateBestSolution(int iteration);

public:
    GRASP_TSP(std::string path, int n, int t, double p, double l, double alpha = 0.2);
    
    ll solve() override;
};