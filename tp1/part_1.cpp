#include "classes/tsp_p1.h"

int main() {
    std::ofstream out("output/part_1.txt");

    LocalSearchTSP tsp1("tsplib-master/burma14.tsp", 14, 14, 0, 0);
    out << tsp1.solve() << '\n';
    tsp1.putOddEvenOrder();
    out << tsp1.solve() << '\n';

    LocalSearchTSP tsp2("tsplib-master/berlin52.tsp", 52, 52, 0, 0);
    out << tsp2.solve() << '\n';
    tsp2.putOddEvenOrder();
    out << tsp2.solve() << '\n';

    LocalSearchTSP tsp3("tsplib-master/st70.tsp", 70, 70, 0, 0);
    out << tsp3.solve() << '\n';
    tsp3.putOddEvenOrder();
    out << tsp3.solve() << '\n';

    LocalSearchTSP tsp4("tsplib-master/gil262.tsp", 262, 262, 0, 0);
    out << tsp4.solve() << '\n';
    tsp4.putOddEvenOrder();
    out << tsp4.solve() << '\n';

    LocalSearchTSP tsp5("tsplib-master/gr666.tsp", 666, 666, 0, 0);
    out << tsp5.solve() << '\n';
    tsp5.putOddEvenOrder();
    out << tsp5.solve() << '\n';
    
    LocalSearchTSP tsp6("tsplib-master/dsj1000.tsp", 1000, 1000, 0, 0);
    out << tsp6.solve() << '\n';
    tsp6.putOddEvenOrder();
    out << tsp6.solve() << '\n';

    LocalSearchTSP tsp7("tsplib-master/burma14.tsp", 14, 2, 1, 2);
    out << tsp7.solve() << '\n';
    tsp7.restartNew(4, 1, 2);
    out << tsp7.solve() << '\n';
    tsp7.restartNew(4, 2, 2);
    out << tsp7.solve() << '\n';

    LocalSearchTSP tsp8("tsplib-master/berlin52.tsp", 52, 10, 200, 400);
    out << tsp8.solve() << '\n';
    tsp8.restartNew(15, 100, 300);
    out << tsp8.solve() << '\n';
    tsp8.restartNew(15, 200, 300);
    out << tsp8.solve() << '\n';

    LocalSearchTSP tsp9("tsplib-master/st70.tsp", 70, 15, 2, 8);
    out << tsp9.solve() << '\n';
    tsp9.restartNew(15, 6, 8);
    out << tsp9.solve() << '\n';
    tsp9.restartNew(10, 6, 10);
    out << tsp9.solve() << '\n';
    tsp9.restartNew(10, 10, 15);
    out << tsp9.solve() << '\n';

    LocalSearchTSP tsp10("tsplib-master/gil262.tsp", 262, 30, 7, 12);
    out << tsp10.solve() << '\n';
    tsp10.restartNew(30, 5, 12);
    out << tsp10.solve() << '\n';

    out.close();
}