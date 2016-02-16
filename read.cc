#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <map>
#include "Dictionary.h"
using namespace std;

int main()
{
	Dictionary dict;
	//openFile("source.txt", dict);
	string command;
	string zy, xin, yvn, binlih, diao, kaxih;
	string new_kaxih;
	cout << ">>";
	while(cin >> command) {
		if(command == "add") {
			if(!dict.empty()) {
				cin >> zy >> xin >> yvn >> binlih >> diao >> kaxih;
				if(dict.add(zy,xin,yvn,binlih,diao,kaxih))
					cout << "Add Successed." << endl;
			}
			else cout << "请先打开一个数据文件！"<<endl;
		}
		else if(command == "create") {
			cin >> zy;
			dict.create(zy);
		}
		else if(command == "open") {
			cin >> zy;
			dict.open(zy);
		}
		else if(command == "delzy") {
			if(!dict.empty()) {
				cin >> zy;
				if(!dict.remove(zy)) cout << "Not Found: " << zy << endl;
			}
			else cout << "请先打开一个数据文件！"<<endl;
		}
		else if(command == "delin") {
			if(!dict.empty()) {
				cin >> zy >> xin >> yvn;
				if(!dict.remove(zy,xin,yvn)) cout << "Not Found: " << xin << yvn << endl;
			}
			else cout << "请先打开一个数据文件！"<<endl;
		}
		else if(command == "deldiao") {
			if(!dict.empty()) {
				cin >> zy >> xin >> yvn >> diao;
				if(!dict.remove(zy,xin,yvn,diao)) cout << "Not Found: " << xin << yvn << diao << endl;
			}
			else cout << "请先打开一个数据文件！"<<endl;
		}
		else if(command == "delkaxih") {
			if(!dict.empty()) {
				cin >> zy >> xin >> yvn >> diao >> kaxih;
				if(!dict.remove(zy,xin,yvn,diao,kaxih)) cout << "Not Found: " << xin << yvn << diao << kaxih << endl;
			}
			else cout << "请先打开一个数据文件！"<<endl;
		}
		else if(command == "show") {
			dict.print(cout);
		}
		else if(command == "up") {
			//cin >> zy >> xin >> yvn >> diao >> kaxih >> new_kaxih;
		}
		else if(command == "save") {
			if(!dict.empty()) {
				cin >> zy;
				ofstream out(zy);
				dict.print(out);
				out.close();
			}
			else cout << "请先打开一个数据文件！"<<endl;
		}
		cout << ">>";
	}
	//ofstream out("output.skk");
	//output(out, dict);
	//out.close();
	//output(cout, dict);
}
