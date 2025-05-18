#include "classes/tsp_p2.h"

int main() {
    std::ofstream out("output/part_2.txt");
    std::ofstream out_greedy("output/part_2_greedy.txt");

    GreedyTSP tsp1("tsplib-master/burma14.tsp", 14, 14, 0, 0);
    out_greedy << tsp1.greedyInitialization(false) << '\n';
    out << tsp1.solve() << '\n';
    tsp1.putOddEvenOrder();
    out_greedy << tsp1.greedyInitialization(true) << '\n';
    out << tsp1.solve() << '\n';

    GreedyTSP tsp2("tsplib-master/berlin52.tsp", 52, 52, 0, 0);
    out_greedy << tsp2.greedyInitialization(false) << '\n';
    out << tsp2.solve() << '\n';
    tsp2.putOddEvenOrder();
    out_greedy << tsp2.greedyInitialization(true) << '\n';
    out << tsp2.solve() << '\n';

    GreedyTSP tsp3("tsplib-master/st70.tsp", 70, 70, 0, 0);
    out_greedy << tsp3.greedyInitialization(false) << '\n';
    out << tsp3.solve() << '\n';
    tsp3.putOddEvenOrder();
    out_greedy << tsp3.greedyInitialization(true) << '\n';
    out << tsp3.solve() << '\n';

    GreedyTSP tsp4("tsplib-master/gil262.tsp", 262, 262, 0, 0);
    out_greedy << tsp4.greedyInitialization(false) << '\n';
    out << tsp4.solve() << '\n';
    tsp4.putOddEvenOrder();
    out_greedy << tsp4.greedyInitialization(true) << '\n';
    out << tsp4.solve() << '\n';

    GreedyTSP tsp5("tsplib-master/gr666.tsp", 666, 666, 0, 0);
    out_greedy << tsp5.greedyInitialization(false) << '\n';
    out << tsp5.solve() << '\n';
    tsp5.putOddEvenOrder();
    out_greedy << tsp5.greedyInitialization(true) << '\n';
    out << tsp5.solve() << '\n';
    
    GreedyTSP tsp6("tsplib-master/dsj1000.tsp", 1000, 1000, 0, 0);
    out_greedy << tsp6.greedyInitialization(false) << '\n';
    out << tsp6.solve() << '\n';
    tsp6.putOddEvenOrder();
    out_greedy << tsp6.greedyInitialization(true) << '\n';
    out << tsp6.solve() << '\n';

    GreedyTSP tsp7("tsplib-master/burma14.tsp", 14, 2, 1, 2);
    out_greedy << tsp7.greedyInitialization(false) << '\n';
    out << tsp7.solve() << '\n';
    tsp7.restartNew(4, 1, 2);
    out_greedy << tsp7.greedyInitialization(false) << '\n';
    out << tsp7.solve() << '\n';
    tsp7.restartNew(4, 2, 2);
    out_greedy << tsp7.greedyInitialization(false) << '\n';
    out << tsp7.solve() << '\n';

    GreedyTSP tsp8("tsplib-master/berlin52.tsp", 52, 10, 200, 400);
    out_greedy << tsp8.greedyInitialization(false) << '\n';
    out << tsp8.solve() << '\n';
    tsp8.restartNew(15, 100, 300);
    out_greedy << tsp8.greedyInitialization(false) << '\n';
    out << tsp8.solve() << '\n';
    tsp8.restartNew(15, 200, 300);
    out_greedy << tsp8.greedyInitialization(false) << '\n';
    out << tsp8.solve() << '\n';

    GreedyTSP tsp9("tsplib-master/st70.tsp", 70, 15, 2, 8);
    out_greedy << tsp9.greedyInitialization(false) << '\n';
    out << tsp9.solve() << '\n';
    tsp9.restartNew(15, 6, 8);
    out_greedy << tsp9.greedyInitialization(false) << '\n';
    out << tsp9.solve() << '\n';
    tsp9.restartNew(10, 6, 10);
    out_greedy << tsp9.greedyInitialization(false) << '\n';
    out << tsp9.solve() << '\n';
    tsp9.restartNew(10, 10, 15);
    out_greedy << tsp9.greedyInitialization(false) << '\n';
    out << tsp9.solve() << '\n';

    GreedyTSP tsp10("tsplib-master/gil262.tsp", 262, 30, 7, 12);
    out_greedy << tsp10.greedyInitialization(false) << '\n';
    out << tsp10.solve() << '\n';
    tsp10.restartNew(30, 5, 12);
    out_greedy << tsp10.greedyInitialization(false) << '\n';
    out << tsp10.solve() << '\n';

    out.close();
}