Read:split.o Read.o
	g++ -o Read split.o Read.o -std=c++11
Read.o:Read.cc
	g++ -o Read.o -c Read.cc -std=c++11
split.o:split.cc
	g++ -o split.o -c split.cc -std=c++11
