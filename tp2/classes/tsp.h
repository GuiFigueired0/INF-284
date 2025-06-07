#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

#define ll long long

class Solution {
public:
    ll value;
    int iteration; 
    std::vector<int> order;

    Solution();
    Solution(const Solution &other);
    Solution(ll v, int t, const std::vector<int> &o);

	Solution& operator=(const Solution &other);
	bool operator==(const Solution &other);

    int dist(const Solution &other);
};

class TSP {
private:
    int m_n, m_t;
    double m_p, m_l;
    std::vector<std::pair<double, double>> m_coordinates;

protected:
    int m_usedT;
    double m_solutionValue;
    Solution m_bestSolution;
    std::vector<int> m_solutionOrder;

private:
    void m_loadData(const std::string& path);
    
protected:
    double m_euclideanDistance(ll i, ll j, bool isPos = true);
    double m_removeEdge(int i, int j, bool isPos = true);
    double m_addEdge(int i, int j, bool isPos = true);
    double m_evaluateSolution();

    void m_greedyInitialization();
    void m_greedyDistInitialization();
    ll m_localSearch();
    ll m_hillClimbing();

public:
    TSP(std::string path, int n, int t, double p, double l);

    int getSize();
    ll evaluateOrder(std::string order);
    const Solution& getBestSolution() const;
    void restartNew(int new_t = -1, double new_p = -1, double new_l = -1);

    virtual ll solve() = 0;
};