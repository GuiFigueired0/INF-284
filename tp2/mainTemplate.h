// ##########################################################
// ##### THIS FILE WAS WRITTEN WITH THE HELP OF CHATGPT #####
// ########################################################## 
/* 
The idea of this file is to create a template for the run of the metaheuristics
that saves the results in a .csv file. This version doesn't erase instances that 
were previously run but don't have a new run.
*/

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <limits>
#include <iomanip>
#include <iostream>

std::map<std::string, std::string> readExistingResults(const std::string &filename) {
    std::map<std::string, std::string> lines;
    std::ifstream in(filename);
    std::string line;

    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string key;
        std::getline(ss, key, ',');

        lines[key] = line;
    }

    in.close();
    return lines;
}

template<class T>
void mainRun(std::string outputfile) {
    std::map<std::string, std::string> results = readExistingResults(outputfile);

    auto runAndCheck = [&](const std::string &filename, std::string inst_label, int n, int t, double p, double l) {
        std::cout << "Instance " << inst_label << std::endl;

        int bestVal = std::numeric_limits<int>::max();
        int bestIt = -1;
        std::vector<int> bestOrder;
        std::vector<int> allVals;

        for (int i = 0; i < 5; ++i) {
            T tsp(filename, n, t, p, l);
            tsp.solve();

            int val = tsp.getBestSolution().value;
            int it = tsp.getBestSolution().iteration;
            std::vector<int> order = tsp.getBestSolution().order;

            allVals.push_back(val);

            if (val < bestVal) {
                bestVal = val;
                bestIt = it;
                bestOrder = order;
            }
        }

        double mean = 0;
        for (int v : allVals) mean += v;
        mean /= allVals.size();
        int meanRounded = static_cast<int>(std::round(mean));

        std::stringstream line;
        line << inst_label << "," << meanRounded << "," << bestVal << "," << bestIt << ",";

        for (int i : bestOrder)
            line << i << " ";

        results[inst_label] = line.str();
    };

    // runAndCheck("tsplib-master/burma14.tsp", "inst_1", 14, 14, 0, 0);
    runAndCheck("tsplib-master/burma14.tsp", "inst_2", 14, 2, 1, 2);
    // runAndCheck("tsplib-master/burma14.tsp", "inst_3", 14, 4, 1, 2);
    // runAndCheck("tsplib-master/burma14.tsp", "inst_4", 14, 4, 2, 2);
    // runAndCheck("tsplib-master/berlin52.tsp", "inst_5", 52, 52, 0, 0);
    // runAndCheck("tsplib-master/berlin52.tsp", "inst_6", 52, 10, 200, 400);
    // runAndCheck("tsplib-master/berlin52.tsp", "inst_7", 52, 15, 100, 300);
    // runAndCheck("tsplib-master/berlin52.tsp", "inst_8", 52, 15, 200, 300);
    // runAndCheck("tsplib-master/st70.tsp", "inst_9", 70, 70, 0, 0);
    // runAndCheck("tsplib-master/st70.tsp", "inst_10", 70, 15, 2, 8);
    // runAndCheck("tsplib-master/st70.tsp", "inst_11", 70, 15, 6, 8);
    // runAndCheck("tsplib-master/st70.tsp", "inst_12", 70, 10, 6, 10);
    // runAndCheck("tsplib-master/st70.tsp", "inst_13", 70, 10, 10, 15);
    // runAndCheck("tsplib-master/gil262.tsp", "inst_14", 262, 262, 0, 0);
    // runAndCheck("tsplib-master/gil262.tsp", "inst_15", 262, 30, 7, 12);
    // runAndCheck("tsplib-master/gil262.tsp", "inst_16", 262, 30, 5, 12);
    // runAndCheck("tsplib-master/gr666.tsp", "inst_17", 666, 666, 0, 0);
    // runAndCheck("tsplib-master/dsj1000.tsp", "inst_18", 1000, 1000, 0, 0);

    std::ofstream out(outputfile);
    for (auto value: results) {
        out << value.second << '\n';
    }
    out.close();
}
