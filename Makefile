read:split.o read.o Dictionary.o
	g++ -o read split.o read.o Dictionary.o -std=c++11
read.o:read.cc
	g++ -o read.o -c read.cc -std=c++11
Dictionary.o:Dictionary.cc
	g++ -o Dictionary.o -c Dictionary.cc -std=c++11
split.o:split.cc
	g++ -o split.o -c split.cc -std=c++11
