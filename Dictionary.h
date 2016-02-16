#ifndef __BENO_DICTIONARY_H__
#define __BENO_DICTIONARY_H__
#include <fstream>
#include <map>
#include "split.h"
using namespace std;

struct In
{
	string xin;
	string yvn;
	string binlih;
	map<string, vector<string>> diao_map;
};

class Dictionary
{
	public:
		Dictionary();
		void create(const string& fileName);
		void open(const string& fileName);
		bool add(const string& zy, string xin,
			string yvn, string binlih,
			string diao, string kaxih);
		bool remove(const string& zy);
		bool remove(const string& zy, string xin, string yvn);
		bool remove(const string& zy, string xin, string yvn, string diao);
		bool remove(const string& zy, string xin, string yvn, string diao, string kaxih);
		void print(ostream& out) const;
		void printTXT(ostream& out) const;
		bool empty() const;
	private:
		void openTXTFile(const string& fileName);
		void openSKKFile(const string& fileName);
		In addIn(const string& xin, const string& yvn,
			const string& binlih, const string& diao,
			const string& kaxih);
		map<string, vector<In>> dict;
};

#endif
