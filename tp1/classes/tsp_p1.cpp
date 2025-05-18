#include "tsp_p1.h"

LocalSearchTSP::LocalSearchTSP(std::string path, int n, int t, double p, double l)
: TSP(path, n, t, p, l) 
{}

ll LocalSearchTSP::solve() {
    // std::cout << "começando\n"; // DEBUG
    m_evaluateSolution();
    
    while (true) {
        std::pair<int,int> bestPair;
        double bestValue = m_solutionValue;
        for (int i=1; i<getSize()-1; i++) {
            for (int j=i+1; j<getSize(); j++) {
                // ### Going 
                m_removeEdge(i-1, i);
                m_removeEdge(j, (j+1)%getSize());
                m_addEdge(i-1, j);
                m_addEdge(i, (j+1)%getSize());
                
                // ### Evaluation
                if (m_solutionValue < bestValue) {
                    bestValue = m_solutionValue; 
                    bestPair = std::make_pair(i, j);
                }

                // ### Back 
                m_removeEdge(i-1, j);
                m_removeEdge(i, (j+1)%getSize());
                m_addEdge(i-1, i);
                m_addEdge(j, (j+1)%getSize());
            }
        }

        if (m_solutionValue <= bestValue) 
            break;
        // std::cout << m_solutionValue << std::endl; // DEBUG

        int i = bestPair.first, j = bestPair.second;
        m_removeEdge(i-1, i);
        m_removeEdge(j, (j+1)%getSize());
        m_addEdge(i-1, j);
        m_addEdge(i, (j+1)%getSize());
        while (i < j) 
            std::swap(m_solutionOrder[i++], m_solutionOrder[j--]);
    }

    return std::round(m_solutionValue);
}