#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <map>
#include "split.h"
using namespace std;

locale loc(""); //linux下配置utf-8;

struct In
{
		wstring xin;
		wstring yvn;
		wstring binlih;
		map<wstring, vector<wstring>> diaos;
};

void wopenSKFile(const string& fileName, map<wstring, vector<In>>& dict)
{
	//wcout << fileName.c_str() << endl;
	wifstream win(fileName);
	if(!win)
	{
		wcout << L"打开文件出错！" << endl;
		return;
	}
	wstring line_before;
	while(getline(win, line_before)) {//一行一字
		if(line_before==L"") continue;
		vector<wstring> line_after;
		split(line_before, L"?", line_after); //拆分字、音：       干        k#on#1:天干;5:事干|k#an#1;5
		wstring zy = line_after[0]; //存字：             干
		wstring in_before = line_after[1]; //存音：             k#on#1:天干;5:事干|k#an#1;5
		vector<In> in;
		vector<wstring> in_after;
		split(in_before, L"|", in_after); //拆音：            k#on#1:天干;5:事干    k#an#1;5
		for(auto each_in : in_after) //每个音：            k#on#1:天干;5:事干
		{
			In i;
			vector<wstring> each_in_after;
			split(each_in, L"_", each_in_after); //拆声、韵、调：      k    on    1:天干;5:事干
			i.xin = each_in_after[0]; //存声 k
			i.yvn = each_in_after[1]; //存韵 on
			i.binlih = each_in_after[2]; //存频率
			wstring diao_before = each_in_after[2]; //存调 1:天干&5:事干
			map<wstring, vector<wstring>> diaos;
			vector<wstring> diao_after;
			split(diao_before,L"&", diao_after); //    1:天干  5:事干
			for(auto each_diao : diao_after)  // 1:天干
			{
				vector<wstring> each_diao_after;
				split(each_diao, L":", each_diao_after);
				wstring diao = each_diao_after[0]; // 1
				vector<wstring> kaxihs;
				if(each_diao_after.size()>1) {
					wstring kaxih_before = each_diao_after[1]; // 天干;干支
					split(kaxih_before, L";", kaxihs);
				}
				i.diaos[diao]=kaxihs;
			}
			in.push_back(i);
		}
		dict[zy] = in;
	}
	win.close();
}

In addIn(const wstring& xin, const wstring& yvn,
			const wstring& binlih, const wstring& diao,
			const wstring& kaxih)
{
	In in;
	in.xin = xin;
	in.yvn = yvn;
	in.binlih = binlih;
	map<wstring, vector<wstring>> diaos;
	vector<wstring> kaxihs;
	if(kaxih!=L"") kaxihs.push_back(kaxih);
	in.diaos[diao]=kaxihs;
	return in;
}

void wopenTXTFile(const string& fileName, map<wstring, vector<In>>& dict)
{
	//wcout << fileName.c_str() << endl;
	wifstream win(fileName);
	if(!win)
	{
		wcout << L"打开文件出错！" << endl;
		return;
	}
	wstring line;
	wstringstream wss;
	wstring zy, xin, binlih, yvn, diao, kaxih;
	while(getline(win, line) ) { //一行
		if(line==L"") continue;
		vector<wstring> input;
		split(line, L"\t", input);
		zy = input.at(0);
		xin = input.at(1);
		yvn = input.at(2);
		binlih = input.at(3);
		diao = input.at(4);
		kaxih = input.at(5);
		if(dict.find(zy)==dict.end())
		{
			//wcout << L"(1)呒" << zy << xin << yvn << diao << L",加字."<<endl;
			vector<In> ins;
			ins.push_back(addIn(xin,yvn,binlih,diao,kaxih));
			dict[zy] = ins;
			continue;
		}
		else
		{
			//wcout << L"(2)有" << zy << ",";
			auto begin_dict = dict[zy].begin(), end_dict = dict[zy].end();
			while(begin_dict!=end_dict)
			{
				//wcout << L"(3)寻" <<xin << yvn << diao <<",";
				if(begin_dict->xin == xin && begin_dict->yvn == yvn)
				{
					//wcout << L"(4)有音" << xin << yvn << ",";
					if(begin_dict->diaos.find(diao)==begin_dict->diaos.end())
					{
						//wcout << L"呒调" << diao << L",加调."<<endl;
						vector<wstring> kaxihs;
						if(kaxih!=L"") {
							//wcout << kaxih <<"_"<< kaxih.length() <<endl;
							kaxihs.push_back(kaxih);
						}
						begin_dict->diaos[diao]=kaxihs;
					}
					break;
				}
				//wcout << L"继续寻！" << endl;
				++begin_dict;
			}
			if(begin_dict==end_dict)
			{
				//wcout << L"(3)呒音" << xin << yvn << diao << L",加音."<<endl;
				dict[zy].push_back(addIn(xin,yvn,binlih,diao,kaxih));
			}
		}
		wss.clear();
	}
	win.close();
}

void wopenFile(const string& fileName, map<wstring, vector<In>>& dict)
{
	string kakxih = fileName.substr(fileName.find_last_of("."),4);
	if(kakxih == ".txt")
		wopenTXTFile(fileName, dict);
	else
		wopenSKFile(fileName, dict);
}

void woutput(wostream& wout, const map<wstring, vector<In>>& dict)
{	//读取
	for(auto word : dict)
	{
		wout << word.first << L"?";
		bool first_word = true;
		for(auto in : word.second)
		{
			if(!first_word) wout << L"|";
			else first_word = false;
			wout << in.xin << L"_";
			wout << in.yvn << L"_";
			wout << in.binlih << L"_";
			bool first_diao = true;
			for(auto diao : in.diaos)
			{
				if(!first_diao) wout << L"&";
				else first_diao = false;
				wout << diao.first;
				if(diao.second.size()) {
					wout << L":";
					bool first = true;
					for(auto kaxih : diao.second)
					{
						if(!first) wout << L";";
						else first = false;
						wout << kaxih;
					}
				}
			}
		}
		wout << endl;
	}
}

int main()
{
	locale::global(loc);
	map<wstring, vector<In>> dict;
	wopenFile("source.txt", dict);
	//wopenFile("source.txt", dict);
	wofstream wout("output.skk");
	woutput(wout, dict);
	wout.close();
	//woutput(wcout, dict);
}
