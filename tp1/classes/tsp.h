#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#define ll long long

class TSP {
private:
    int m_n, m_t, m_usedT;
    double m_p, m_l;
    std::vector<std::pair<double, double>> m_coordinates;

protected:
    double m_solutionValue;
    std::vector<int> m_solutionOrder;

private:
    void m_loadData(const std::string& path);
    
protected:
    // ### Start Part 0:
    double m_euclideanDistance(ll i, ll j, bool isPos = true);
    void m_removeEdge(int i, int j);
    void m_addEdge(int i, int j);
    double m_evaluateSolution();
    // ### End Part 0:

public:
    TSP(std::string path, int n, int t, double p, double l);

    int getSize();
    void putOddEvenOrder();
    void restartNew(int new_t = -1, double new_p = -1, double new_l = -1);

    virtual ll solve() = 0;
};