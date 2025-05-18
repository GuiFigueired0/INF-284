#include <list>
#include <limits>
#include "tsp_p2.h"

GreedyTSP::GreedyTSP(std::string path, int n, int t, double p, double l)
: LocalSearchTSP(path, n, t, p, l) 
{}

ll GreedyTSP::greedyInitialization(bool bothSides) {
    std::list<int> aux;
    aux.emplace_back(0);

    for (int i=1; i<getSize(); i++) { // Like Selection Sort + list (to add in both ends)
        bool addBack = true;
        std::pair<double, int> currentBest(std::numeric_limits<double>::max(), -1);
        for (int j=i; j<getSize(); j++){
            bool back = true;
            double dist = m_euclideanDistance(aux.back(), m_solutionOrder[j], false);

            if (bothSides) {
                double front_dist = m_euclideanDistance(aux.front(), m_solutionOrder[j], false);
                if (front_dist < dist) {
                    dist = front_dist; 
                    back = false;
                }
            }
            
            if (dist < currentBest.first) {
                addBack = back;
                currentBest = {dist, j};
            }
        }

        std::swap(m_solutionOrder[i], m_solutionOrder[currentBest.second]);
        int x = m_solutionOrder[i];
        if (addBack)
            aux.emplace_back(x);
        else 
            aux.emplace_front(x);
    }

    int i=0;
    for (int elem: aux) 
        m_solutionOrder[i++] = elem;
    
    m_evaluateSolution();
    return std::round(m_solutionValue);
}