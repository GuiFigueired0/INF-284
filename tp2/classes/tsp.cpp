#include "tsp.h"

#include <list>
#include <sstream>

// SOLUTION

Solution::Solution() 
{}

Solution::Solution(const Solution &other) {
    *this = other;
}

Solution::Solution(ll v, int t, const std::vector<int> &o) {
    value = v; 
    iteration = t; 
    order = o;
}

Solution& Solution::operator=(const Solution &other) {
    if (this==&other) 
        return *this;

    value = other.value; 
    iteration = other.iteration; 
    order = other.order;

    return *this;
}

bool Solution::operator==(const Solution &other) {
    if (value != other.value) 
        return false;
    for (int i=0; i<order.size(); i++)
        if (order[i] != other.order[i])
            return false;
    return true;
}

int Solution::dist(const Solution &other) {
    if (order.size() != other.order.size()) return -1;
    int total = 0;
    for (int i=0; i<order.size(); i++)
        total += order[i] != other.order[i];
    return total;
}

// TSP

void TSP::m_loadData(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo: " << path << '\n';
        return;
    }

    std::string line;
    m_coordinates.clear();
    bool readingNodes = false;
    while (std::getline(file, line)) {
        if (line == "NODE_COORD_SECTION") {
            readingNodes = true;
            continue;
        }
        if (line == "EOF") break;

        if (readingNodes) {
            std::stringstream ss(line);
            std::string cityId; 
            double x, y;
            ss >> cityId >> x >> y;
            m_coordinates.emplace_back(x, y);
        }
    }
}

double TSP::m_euclideanDistance(ll i, ll j, bool isPos) {
    long long x = i, y = j;
    if (isPos) {
        x = m_solutionOrder[i];
        y = m_solutionOrder[j];
    }
    return std::round(std::sqrt(std::pow(m_coordinates[x].first - m_coordinates[y].first, 2) + std::pow(m_coordinates[x].second - m_coordinates[y].second, 2)));
}

double TSP::m_removeEdge(int i, int j, bool isPos) {
    double x = m_euclideanDistance(i, j, isPos);
    if (x <= m_l)
        if (m_usedT-- > m_t)
            x += m_p;
    m_solutionValue -= x;
    return x;
}

double TSP::m_addEdge(int i, int j, bool isPos) {
    double x = m_euclideanDistance(i, j, isPos);
    if (x <= m_l)
        if (++m_usedT > m_t)
            x += m_p;
    m_solutionValue += x;
    return x;
}

double TSP::m_evaluateSolution() {
    m_usedT = 0;
    m_solutionValue = 0.0;
    for (size_t i=0; i<m_solutionOrder.size()-1; i++)
        m_addEdge(i, i+1);
    m_addEdge(0, getSize()-1);
    return m_solutionValue;
}

void TSP::m_greedyDistInitialization() {
    std::list<int> aux;
    aux.emplace_back(0);
    auto it0 = aux.begin();

    for (int i=1; i<getSize(); i++) { // Like Selection Sort + list (to add in both ends)
        bool addBack = true;
        std::pair<double, int> currentBest(std::numeric_limits<double>::max(), -1);
        for (int j=i; j<getSize(); j++){
            bool back = true;
            double dist = m_euclideanDistance(aux.back(), m_solutionOrder[j], false);

            double front_dist = m_euclideanDistance(aux.front(), m_solutionOrder[j], false);
            if (front_dist < dist) {
                dist = front_dist; 
                back = false;
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
    for (auto it = it0; it != aux.end(); it++)
        m_solutionOrder[i++] = *it; 
    for (auto it = aux.begin(); it != it0; it++)
        m_solutionOrder[i++] = *it; 
    
    m_evaluateSolution();
}

void TSP::m_greedyInitialization() {
    std::list<int> aux;
    aux.emplace_back(0);
    auto it0 = aux.begin();
    m_solutionValue = m_usedT = 0;

    for (int i=1; i<getSize(); i++) {
        bool addBack = true;
        std::pair<double, int> currentBest(std::numeric_limits<double>::max(), -1);
        for (int j=i; j<getSize(); j++){
            bool back = true;
            double dist = m_addEdge(aux.back(), m_solutionOrder[j], false);
            m_removeEdge(aux.back(), m_solutionOrder[j], false);

            double front_dist = m_addEdge(aux.front(), m_solutionOrder[j], false);
            m_removeEdge(aux.front(), m_solutionOrder[j], false);
            if (front_dist < dist) {
                dist = front_dist; 
                back = false;
            }
            
            if (dist < currentBest.first) {
                addBack = back;
                currentBest = {dist, j};
            }
        }

        std::swap(m_solutionOrder[i], m_solutionOrder[currentBest.second]);
        int x = m_solutionOrder[i];
        if (addBack) {
            m_addEdge(aux.back(), x, false);
            aux.emplace_back(x);
        } else {
            m_addEdge(aux.front(), x, false);
            aux.emplace_front(x);
        } 
    }

    int i=0;
    for (auto it = it0; it != aux.end(); it++)
        m_solutionOrder[i++] = *it; 
    for (auto it = aux.begin(); it != it0; it++)
        m_solutionOrder[i++] = *it;  

    m_addEdge(0, getSize()-1);
}

ll TSP::m_localSearch() {
    m_evaluateSolution();
    
    while (true) {
        bool improved = false;

        for (int i=1; i<getSize()-1; i++) {
            for (int j=i+1; j<getSize(); j++) {
                double oldValue = m_solutionValue;

                m_removeEdge(i-1, i);
                m_removeEdge(j, (j+1)%getSize());
                m_addEdge(i-1, j);
                m_addEdge(i, (j+1)%getSize());
                
                if (m_solutionValue < oldValue) {
                    improved = true;
                    int auxI = i, auxJ = j;
                    while (auxI < auxJ) 
                        std::swap(m_solutionOrder[auxI++], m_solutionOrder[auxJ--]);
                } else {
                    m_removeEdge(i-1, j);
                    m_removeEdge(i, (j+1)%getSize());
                    m_addEdge(i-1, i);
                    m_addEdge(j, (j+1)%getSize());
                }
            }
        }

        if (!improved) 
            break;
    }

    return std::round(m_solutionValue);
}

ll TSP::m_hillClimbing() {
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

TSP::TSP(std::string path, int n, int t, double p, double l): 
m_n(n), m_t(t), m_p(p), m_l(l), m_usedT(0), m_solutionValue(0.0), m_bestSolution(Solution(10e10, -1, std::vector<int>())), m_solutionOrder(n) 
{
    m_loadData(path);

    for (int i=0; i<n; i++)
        m_solutionOrder[i] = i;
}

int TSP::getSize() {
    return m_n;
}

ll TSP::evaluateOrder(std::string order) {
    int x;
    std::stringstream ss(order);
    for (int i=0; i<getSize(); i++) {
        ss >> x;
        m_solutionOrder[i] = x;
    }
    return m_evaluateSolution();
}

const Solution& TSP::getBestSolution() const {
    return m_bestSolution;
}

void TSP::restartNew(int new_t, double new_p, double new_l) {
    if (new_t != -1)
        m_t = new_t; 
    if (new_p != -1)
        m_p = new_p; 
    if (new_l != -1) 
        m_l = new_l; 

    m_usedT = 0;
    m_solutionValue = 0.0;
    for (int i=0; i<getSize(); i++)
        m_solutionOrder[i] = i;
}
