all: bin/mutator

bin/mutator: 
	g++ -O2 -std=c++11 src/mutator.cpp -o bin/mutator

test: bin/mutator
	./bin/mutator data/test.fq data/out.fq 9600 0.1

clean: 
	rm ./bin/*
	rm ./data/out.fq
