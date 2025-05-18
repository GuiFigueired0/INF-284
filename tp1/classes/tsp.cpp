#include "tsp.h"

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

// ### Start Part 0:
double TSP::m_euclideanDistance(ll i, ll j, bool isPos) {
    long long x = i, y = j;
    if (isPos) {
        x = m_solutionOrder[i];
        y = m_solutionOrder[j];
    }
    return std::round(std::sqrt(std::pow(m_coordinates[x].first - m_coordinates[y].first, 2) + std::pow(m_coordinates[x].second - m_coordinates[y].second, 2)));
}

void TSP::m_removeEdge(int i, int j) {
    double x = m_euclideanDistance(i, j);
    if (x <= m_l)
        if (m_usedT-- > m_t)
            x += m_p;
    m_solutionValue -= x;
}

void TSP::m_addEdge(int i, int j) {
    double x = m_euclideanDistance(i, j);
    if (x <= m_l)
        if (++m_usedT > m_t)
            x += m_p;
    m_solutionValue += x;
}

double TSP::m_evaluateSolution() {
    m_usedT = 0;
    m_solutionValue = 0.0;
    for (size_t i=0; i<m_solutionOrder.size()-1; i++)
        m_addEdge(i, i+1);
    m_addEdge(0, getSize()-1);
    return m_solutionValue;
}
// ### End Part 0

TSP::TSP(std::string path, int n, int t, double p, double l): 
m_n(n), m_t(t), m_usedT(0), m_p(p), m_l(l), m_solutionValue(0.0), m_solutionOrder(n) 
{
    m_loadData(path);

    for (int i=0; i<n; i++)
        m_solutionOrder[i] = i;
}

int TSP::getSize() {
    return m_n;
}

void TSP::putOddEvenOrder() {
    m_solutionOrder = std::vector<int>();
    m_solutionOrder.reserve(getSize());
    for (int i=1; i<=getSize(); i+=2)
        m_solutionOrder.emplace_back(i-1);
    for (int i=2; i<=getSize(); i+=2)
        m_solutionOrder.emplace_back(i-1);
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