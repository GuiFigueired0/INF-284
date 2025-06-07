all: ils grasp test

run_all: run_ils run_grasp

ils:
	g++ ils.cpp classes/tsp.cpp classes/ils_tsp.cpp -o bin/ils

grasp:
	g++ grasp.cpp classes/tsp.cpp classes/ils_tsp.cpp classes/grasp_tsp.cpp -o bin/grasp

test:
	g++ test.cpp classes/tsp.cpp -o bin/test

run_ils:
	./bin/ils

run_grasp:
	./bin/grasp

run_test:
	./bin/test < test.txt
