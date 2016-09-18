#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int main()
{
ifstream infile("words.txt");
set<string> words;

string word;
while(infile >> word)
{
	words.insert(word);
}

for(set<string>::iterator it = words.begin(); it != words.end(); it++)
	{
	cout << *it << endl;
	}

}
