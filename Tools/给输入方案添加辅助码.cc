#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

struct Info
{
	string pihwak;
	map<string, string> im;
};

int main(int argc, char * argv[])
{
	ifstream in("theicieo.dict.yaml");
	string zy, im, bajv;
	map<string, Info> dict;
	while(in >> zy >> im >> bajv)
	{
		dict[zy].im[im]=bajv;
	}
	in.close();
	in.open("stroke.dict.yaml");
	string stroke;
	while(in >> zy >> stroke)
	{
		dict[zy].pihwak = stroke;
	}
	ofstream out("tsttst.txt");
	for(const auto& d : dict) {
		for(const auto& im : d.second.im) {
			out << d.first << "\t";
			out << im.first;
			if(d.second.pihwak!="") out << ";" << d.second.pihwak; //以“;”分割
			out << "\t";
			out << im.second << endl;
		}
	}
}
