all: part_0 part_1 part_2

run_all: run_0 run_1 run_2

part_0:
	g++ part_0.cpp classes/tsp.cpp -o bin/part_0

part_1:
	g++ part_1.cpp classes/tsp.cpp classes/tsp_p1.cpp -o bin/part_1

part_2:
	g++ part_2.cpp classes/tsp.cpp classes/tsp_p1.cpp classes/tsp_p2.cpp -o bin/part_2

run_0:
	./bin/part_0

run_1:
	./bin/part_1

run_2:
	./bin/part_2

clean:
	rm -f bin/* output/*
