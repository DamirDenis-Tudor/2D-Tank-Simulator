#include<iostream>
#include<vector>
#include<map>
#include <set>
using namespace std;

//template <typename T>
int main()
{
	map<set<const char*>, int> assets ;

	assets.insert(pair< set<const char*>, int >({"body" , "color"}, 3));

	cout << assets[{"body" , "color"}];

	return 0;
}