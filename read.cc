#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "split.h"

using namespace std;

struct In
{
		wstring xin;
		wstring yvn;
		map<wstring, vector<wstring>> diaos;
};

int main()
{
	locale loc(""); //linux下配置utf-8
	locale::global(loc);
	wifstream win("words.txt");
	map<wstring, vector<In>> dict;
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
	
	//读取
	for(auto word : dict)
	{
		wcout << word.first << L"?";
		bool first_word = true;
		for(auto in : word.second)
		{
			if(!first_word) wcout << L"|";
			else first_word = false;
			wcout << in.xin << L"_";
			wcout << in.yvn << L"_";
			bool first_diao = true;
			for(auto diao : in.diaos)
			{
				if(!first_diao) wcout << L"&";
				else first_diao = false;
				bool first = true;
				wcout << diao.first;
				if(!diao.second.empty()) {
					wcout << L":";
					for(auto kaxih : diao.second)
					{
						if(!first) wcout << L";";
						else first = false;
						wcout << kaxih;
					}
				}
			}
		}
		wcout << endl;
	}
}
