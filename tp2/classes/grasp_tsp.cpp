#include "grasp_tsp.h"

#include <list>
#include <algorithm>

Solution GRASP_TSP::m_pathRelinking(Solution a, Solution &b, int iteration) {
    Solution bestSolution(a);
    m_solutionOrder = a.order;
    m_evaluateSolution();

    std::vector<int> positions(getSize());
    for (int i=0; i<getSize(); i++) 
        positions[m_solutionOrder[i]] = i;

    while (b.dist(a)) {
        std::pair<double, int> currentBest(std::numeric_limits<double>::max(), -1);
        for (int i=1; i<getSize(); i++){
            if (m_solutionOrder[i] == b.order[i]) continue;
            int j = positions[b.order[i]];

            // ### Going 
            if (abs(i-j) == 1) {
                if (i<j) {
                    m_removeEdge(i-1, i);
                    m_removeEdge(j, (j+1)%getSize());
                    m_addEdge(i-1, j);
                    m_addEdge(i, (j+1)%getSize());
                } else {
                    m_removeEdge(j-1, j);
                    m_removeEdge(i, (i+1)%getSize());
                    m_addEdge(j-1, i);
                    m_addEdge(j, (i+1)%getSize());
                }
            } else {
                m_removeEdge(i-1, i);
                m_removeEdge(i, (i+1)%getSize());
                m_removeEdge(j-1, j);
                m_removeEdge(j, (j+1)%getSize());
                m_addEdge(i-1, j);
                m_addEdge(j, (i+1)%getSize());
                m_addEdge(j-1, i);
                m_addEdge(i, (j+1)%getSize());
            }
            
            // ### Evaluation
            if (m_solutionValue < currentBest.first)
                currentBest = std::make_pair(m_solutionValue, i);

            // ### Back 
            if (abs(i-j) == 1) {
                if (i<j) {
                    m_removeEdge(i-1, j);
                    m_removeEdge(i, (j+1)%getSize());
                    m_addEdge(i-1, i);
                    m_addEdge(j, (j+1)%getSize());
                } else {
                    m_removeEdge(j-1, i);
                    m_removeEdge(j, (i+1)%getSize());
                    m_addEdge(j-1, j);
                    m_addEdge(i, (i+1)%getSize());
                }
            } else {
                m_removeEdge(i-1, j);
                m_removeEdge(j, (i+1)%getSize());
                m_removeEdge(j-1, i);
                m_removeEdge(i, (j+1)%getSize());
                m_addEdge(i-1, i);
                m_addEdge(i, (i+1)%getSize());
                m_addEdge(j-1, j);
                m_addEdge(j, (j+1)%getSize());
            }
        }

        int i = currentBest.second, j = positions[b.order[i]];
        if (abs(i-j) == 1) {
            if (i<j) {
                m_removeEdge(i-1, i);
                m_removeEdge(j, (j+1)%getSize());
                m_addEdge(i-1, j);
                m_addEdge(i, (j+1)%getSize());
            } else {
                m_removeEdge(j-1, j);
                m_removeEdge(i, (i+1)%getSize());
                m_addEdge(j-1, i);
                m_addEdge(j, (i+1)%getSize());
            }
        } else {
            m_removeEdge(i-1, i);
            m_removeEdge(i, (i+1)%getSize());
            m_removeEdge(j-1, j);
            m_removeEdge(j, (j+1)%getSize());
            m_addEdge(i-1, j);
            m_addEdge(j, (i+1)%getSize());
            m_addEdge(j-1, i);
            m_addEdge(i, (j+1)%getSize());
        }
        positions[m_solutionOrder[i]] = j;
        positions[m_solutionOrder[j]] = i;
        std::swap(a.order[i], a.order[j]);
        std::swap(m_solutionOrder[i], m_solutionOrder[j]);

        if (m_solutionValue < bestSolution.value) 
            bestSolution = Solution(m_solutionValue, iteration, m_solutionOrder);
    }
    return bestSolution;
}

void GRASP_TSP::m_GreedyRandomizedConstruction() {
    restartNew();
    std::list<int> aux;
    aux.emplace_back(0);
    auto it0 = aux.begin();

    for (int i=1; i<getSize(); i++) { // Like Selection Sort + list (to add in both ends)
        std::vector<std::pair<double, std::pair<bool,int>>> distances;
        for (int j=i; j<getSize(); j++){
            bool addBack = true;
            double dist = m_euclideanDistance(aux.back(), m_solutionOrder[j], false);

            double front_dist = m_euclideanDistance(aux.front(), m_solutionOrder[j], false);
            if (front_dist < dist) {
                dist = front_dist; 
                addBack = false;
            }
            
            distances.emplace_back(dist, std::make_pair(addBack, j));
        }

        std::sort(distances.begin(), distances.end());
        int p = std::ceil(m_alpha * distances.size());
        int pos = rand() % p;
        std::pair<double, std::pair<bool,int>> chosen = distances[pos];

        std::swap(m_solutionOrder[i], m_solutionOrder[chosen.second.second]);
        int x = m_solutionOrder[i];
        if (chosen.second.first)
            aux.emplace_back(x);
        else 
            aux.emplace_front(x);
    }

    int i=0;
    for (auto it = it0; it != aux.end(); it++)
        m_solutionOrder[i++] = *it; 
    for (auto it = aux.begin(); it != it0; it++)
        m_solutionOrder[i++] = *it; 
    
    m_evaluateSolution();
}

void GRASP_TSP::m_UpdateBestSolution(int iteration) {
    Solution a(m_bestSolution), b(m_solutionValue, iteration, m_solutionOrder);
    if (a==b) return;
    if (a.value > b.value) {
        Solution temp(a); 
        a = b;
        b = temp;
    }
    m_bestSolution = m_pathRelinking(a, b, iteration);
}

GRASP_TSP::GRASP_TSP(std::string path, int n, int t, double p, double l, double alpha)
: m_alpha(alpha), ILS_TSP(path, n, t, p, l) 
{}

ll GRASP_TSP::solve() {
    m_greedyDistInitialization();
    ll initialValue = m_hillClimbing();
    m_bestSolution = Solution(initialValue, 0, m_solutionOrder);
    
    int maxIterations = 25;
    for (int i=0; i<maxIterations; i++) {
        m_GreedyRandomizedConstruction();
        m_hillClimbing();
        m_UpdateBestSolution(i);
    }

    return m_bestSolution.value;
}