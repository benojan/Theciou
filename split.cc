//split函数
#include "split.h"
using namespace std;

void split(const string& src, const string& sep, vector<string>& des)
{
	string substring;
	string::size_type start = 0, index;
	do
	{
		index = src.find_first_of(sep, start);
		if(index != string::npos)
		{
			substring = src.substr(start, index-start);
			des.push_back(substring);
			//start = src.find_first_not_of(sep, index); //设置start为找到的位置之后，即跳过sep
			start = src.find_first_of(sep, start)+sep.size();
			if(start == string::npos) return;
		}
	} while(index != string::npos);
	substring = src.substr(start);
	des.push_back(substring);
}
