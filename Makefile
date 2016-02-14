read:split.o read.o
	g++ -o read split.o read.o -std=c++11
read.o:Read.cc
	g++ -o read.o -c read.cc -std=c++11
split.o:split.cc
	g++ -o split.o -c split.cc -std=c++11
