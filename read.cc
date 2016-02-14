#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "split.h"

using namespace std;

class Diao
{
	public:
		Diao(const wstring& diao,const vector<wstring>& kaxihs):diao(diao),kaxihs(kaxihs){}
		void print() const;
		int num_of_kaxihs() const { return kaxihs.size(); }
	private:
		wstring diao;
		vector<wstring> kaxihs;
};

void Diao::print() const
{
	wcout << diao;
	if(kaxihs.size())
	{
		wcout << L":";
		bool first = true;
		for(auto kaxih: kaxihs)
		{
			if(!first) wcout << L";";
			else first=false;
			wcout << kaxih;
		}
	}
}

class In
{
	public:
		In(const wstring& xin, const wstring& yvn, const vector<Diao>& diaos):xin(xin),yvn(yvn),diaos(diaos){}
		void print() const;
		int num_of_diaos() const { return diaos.size(); }
	private:
		wstring xin;
		wstring yvn;
		vector<Diao> diaos;
};

void In::print() const
{
	wcout << xin << L"_" << yvn << L"_";
	bool first = true;
	for(auto diao : diaos)
	{
		if(!first) wcout << L"&";
		else first=false;
		diao.print();
	}
}

class Word
{
	public:
		Word(const wstring& zy, const vector<In>& ins):zy(zy),ins(ins){}
		wstring getZy() const { return zy; }
		void print() const;
		int num_of_ins() const { return ins.size(); }
	private:
		wstring zy;
		vector<In> ins;
};

void Word::print() const
{
	wcout << zy << L"?";
	bool first = true;
	for(auto in : ins) {
		if(!first) wcout << L"|";
		else first=false;
		in.print();
	}
	wcout << endl;
}

int main()
{
	locale loc(""); //linux下配置utf-8
	locale::global(loc);
	wifstream win("words.txt");
	vector<Word> dict;
	wstring line_before;
	while(getline(win, line_before)) {//一行一字
		if(line_before==L"") continue;
		vector<wstring> line_after;
		split(line_before, L"?", line_after); //拆分字、音：       干        k#on#1:天干;5:事干|k#an#1;5
		wstring zy = line_after[0]; //存字：             干
		wstring in_before = line_after[1]; //存音：             k#on#1:天干;5:事干|k#an#1;5
		vector<In> ins;
		vector<wstring> in_after;
		split(in_before, L"|", in_after); //拆音：            k#on#1:天干;5:事干    k#an#1;5
		for(auto each_in : in_after) //每个音：            k#on#1:天干;5:事干
		{
			vector<wstring> each_in_after;
			split(each_in, L"_", each_in_after); //拆声、韵、调：      k    on    1:天干;5:事干
			wstring xin = each_in_after[0]; //存声 k
			wstring yvn = each_in_after[1]; //存韵 on
			wstring diao_before = each_in_after[2]; //存调 1:天干&5:事干
			vector<Diao> diaos;
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
				Diao d(diao, kaxihs);
				diaos.push_back(d);
			}
			In i(xin, yvn, diaos);
			ins.push_back(i);
		}
		Word w(zy, ins); //新建字
		dict.push_back(w); //添加到字典
	}
	
	//读取
	for(auto word : dict)
	{
		word.print();
	}
}
