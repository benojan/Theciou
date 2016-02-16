#include "Dictionary.h"

Dictionary::Dictionary()
{
}

void Dictionary::create(const string& fileName)
{
	dict.clear();
	open(fileName);
}

bool Dictionary::empty() const
{
	return dict.empty();
}

void Dictionary::open(const string& fileName)
{
	string kakxih = fileName.substr(fileName.find_last_of("."),4);
	if(kakxih == ".txt")
		openTXTFile(fileName);
	else
		openSKKFile(fileName);
}

void Dictionary::openSKKFile(const string& fileName)
{
	//out << fileName.c_str() << endl;
	ifstream in(fileName);
	if(!in)
	{
		cout << "打开文件出错！" << endl;
		return;
	}
	string line_before;
	while(getline(in, line_before)) //一行一字
	{
		if(line_before=="") continue;
		vector<string> line_after;
		split(line_before, "!", line_after); //拆分字、音：       干        k#on#1:天干;5:事干|k#an#1;5
		string zy = line_after[0]; //存字：             干
		string in_before = line_after[1]; //存音：             k#on#1:天干;5:事干|k#an#1;5
		vector<In> in;
		vector<string> in_after;
		split(in_before, "|", in_after); //拆音：            k#on#1:天干;5:事干    k#an#1;5
		for(auto each_in : in_after) //每个音：            k#on#1:天干;5:事干
		{
			In i;
			vector<string> each_in_after;
			split(each_in, "_", each_in_after); //拆声、韵、调：      k    on    1:天干;5:事干
			i.xin = each_in_after[0]; //存声 k
			i.yvn = each_in_after[1]; //存韵 on
			i.binlih = each_in_after[2]; //存频率
			string diao_before = each_in_after[2]; //存调 1:天干&5:事干
			map<string, vector<string>> diao_map;
			vector<string> diao_after;
			split(diao_before,"&", diao_after); //    1:天干  5:事干
			for(auto each_diao : diao_after)  // 1:天干
			{
				vector<string> each_diao_after;
				split(each_diao, ":", each_diao_after);
				string diao = each_diao_after[0]; // 1
				vector<string> kaxihs;
				if(each_diao_after.size()>1) {
					string kaxih_before = each_diao_after[1]; // 天干;干支
					split(kaxih_before, ";", kaxihs);
				}
				i.diao_map[diao]=kaxihs;
			}
			in.push_back(i);
		}
		dict[zy] = in;
	}
	in.close();
}

void Dictionary::openTXTFile(const string& fileName)
{
	//out << fileName.c_str() << endl;
	ifstream in(fileName);
	if(!in)
	{
		cout << "打开文件出错！" << endl;
		return;
	}
	string line;
	string zy, xin, binlih, yvn, diao, kaxih;
	while(getline(in, line) ) //一行
	{
		if(line=="") continue;
		vector<string> input;
		split(line, "\t", input);
		zy = input.at(0);
		xin = input.at(1);
		yvn = input.at(2);
		binlih = input.at(3);
		diao = input.at(4);
		kaxih = input.at(5);
		if(!add(zy,xin,yvn,binlih,diao,kaxih)) cout << "Add Error" << endl;
	}
	in.close();
}

void Dictionary::print(ostream& out) const
{	//读取
	for(auto word : dict)
	{
		out << word.first << "!";
		bool first_word = true;
		for(auto in : word.second)
		{
			if(!first_word) out << "|";
			else first_word = false;
			out << in.xin << "_";
			out << in.yvn << "_";
			out << in.binlih << "_";
			bool first_diao = true;
			for(auto diao : in.diao_map)
			{
				if(!first_diao) out << "&";
				else first_diao = false;
				out << diao.first;
				if(diao.second.size()) {
					out << ":";
					bool first = true;
					for(auto kaxih : diao.second)
					{
						if(!first) out << ";";
						else first = false;
						out << kaxih;
					}
				}
			}
		}
		out << endl;
	}
}

void Dictionary::printTXT(ostream& out) const
{
	for(auto word : dict)
	{
		for(auto in : word.second)
		{
			for(auto diao : in.diao_map)
			{
				out << word.first << "\t";
				out << in.xin << "\t";
				out << in.yvn << "\t";
				out << in.binlih << "\t";
				out << diao.first << "\t";
				if(diao.second.size()) {
					bool first = true;
					for(auto kaxih : diao.second)
					{
						if(!first) out << ";";
						else first = false;
						out << kaxih;
					}
				}
				out << endl;
			}
		}
	}
}

In Dictionary::addIn(const string& xin, const string& yvn,
			const string& binlih, const string& diao,
			const string& kaxih)
{
	In in;
	in.xin = xin;
	in.yvn = yvn;
	in.binlih = binlih;
	map<string, vector<string>> diao_map;
	vector<string> kaxihs;
	if(kaxih!="") kaxihs.push_back(kaxih);
	in.diao_map[diao]=kaxihs;
	return in;
}

bool Dictionary::add(const string& zy, string xin,
		string yvn, string binlih,
		string diao, string kaxih)
{
	if(xin=="?") xin="";
	if(yvn=="?") yvn="";
	if(binlih=="?") binlih="";
	if(diao=="?") diao="";
	if(kaxih=="?") kaxih="";
	
	if(dict.find(zy)==dict.end())
	{
		//cout << "(1)呒" << zy << xin << yvn << diao << ",加字."<<endl;
		vector<In> ins;
		ins.push_back(addIn(xin,yvn,binlih,diao,kaxih));
		dict[zy] = ins;
		//cout << "加字成功!" << endl;
	}
	else
	{
		//cout << "(2)有" << zy << "," <<endl;
		auto begin_dict = dict[zy].begin(), end_dict = dict[zy].end();
		while(begin_dict!=end_dict)
		{
			//cout << "(3)寻" <<xin << yvn << diao <<"," <<endl;
			if(begin_dict->xin == xin && begin_dict->yvn == yvn)
			{
				//cout << "(4)有音" << xin << yvn << "," << endl;
				if(begin_dict->diao_map.find(diao)==begin_dict->diao_map.end())
				{
					//cout << "(6)呒调" << diao << ",加调."<<endl;
					vector<string> kaxihs;
					if(kaxih!="") {
						split(kaxih,";",kaxihs);
					}
					begin_dict->diao_map[diao]=kaxihs;
				}
				else{
					//cout << "(7)有调" << diao << "," << endl;
					if(kaxih!="") {
						auto begin = begin_dict->diao_map[diao].begin(),
							end = begin_dict->diao_map[diao].end();
						while(begin!=end)
						{
							if((*begin)==kaxih) break;
							++begin;
						}
						if(begin==end) {
							//cout << "呒解释" << kaxih << ",加解释." << endl;
							begin_dict->diao_map[diao].push_back(kaxih);
						}
					}
				}
				break;
			}
			//cout << "继续寻！" << endl;
			++begin_dict;
		}
		if(begin_dict==end_dict)
		{
			//cout << "(5)呒音" << xin << yvn << diao << ",加音."<<endl;
			dict[zy].push_back(addIn(xin,yvn,binlih,diao,kaxih));
		}
	}
	return true;
}

bool Dictionary::remove(const string& zy)
{
	if(dict.erase(zy)) return true;
	return false;
}

bool Dictionary::remove(const string& zy, string xin, string yvn)
{
	if(xin=="?") xin="";
	if(yvn=="?") yvn="";
	auto in_vec = dict.find(zy);
	if(in_vec == dict.end() ) { return false; } //字典里没有这个字 及 音vec
	auto begin = in_vec->second.begin();
	auto end = in_vec->second.cend();
	while(begin != end) //遍历 音vec
	{
		if(begin->xin == xin and begin->yvn == yvn) //找到所需的音
		{
			in_vec->second.erase(begin); //删除音
			break; //只要找到就break，使得begin!=end
		}
		++begin;
	}
	if(begin==end) return false; //未找到
	return true;
}

bool Dictionary::remove(const string& zy, string xin, string yvn, string diao)
{
	if(xin=="?") xin="";
	if(yvn=="?") yvn="";
	if(diao=="?") diao="";
	auto in_vec = dict.find(zy);
	if(in_vec == dict.end() ) { //字典里有这个字的 音vec
		cout << "Not Found: " << zy << endl;
		return false;
	}
	auto begin = in_vec->second.begin();
	auto end = in_vec->second.end();
	while(begin!=end) //遍历 音vec
	{
		if(begin->xin == xin && begin->yvn == yvn) //找到所需的音
		{
			auto kaxih_vec = begin->diao_map.find(diao);
			if(kaxih_vec != begin->diao_map.end() ) //找到diao及解释vec
			{
				begin->diao_map.erase(kaxih_vec); //调字典里删除调
				break;
			}
		}
		++begin;
	}
	if(begin==end) return false;
	return true;
}

bool Dictionary::remove(const string& zy, string xin, string yvn, string diao, string kaxih)
{
	if(xin=="?") xin="";
	if(yvn=="?") yvn="";
	if(diao=="?") diao="";
	if(kaxih=="?") kaxih="";
	auto in_vec = dict.find(zy);
	if(in_vec == dict.end() ) { //字典里有这个字的 音vec
		return false;
	}
	auto begin = in_vec->second.begin();
	auto end = in_vec->second.end();
	while(begin!=end) //遍历 音vec
	{
		if(begin->xin == xin && begin->yvn == yvn) //找到所需的音
		{
			auto kaxih_vec = begin->diao_map.find(diao);
			if(kaxih_vec != begin->diao_map.end() ) //找到diao及解释vec
			{
				auto begin_kx = kaxih_vec->second.begin();
				auto end_kx = kaxih_vec->second.begin();
				while(begin_kx!=end_kx)
				{
					if(kaxih == (*begin_kx) ) {
						kaxih_vec->second.erase(begin_kx);
						break;
					}
					++begin_kx;
				}
				break;
			}
		}
		++begin;
	}
	if(begin==end) return false;
	return true;
}
