using namespace std;
#pragma once
#include <string>
#include <list>
#include<vector>
#include "Directory.h"
#include "trienode.h"

struct searchStruct
{
	long int nodeserialnr=-1; //Serial number of vertex array vertices of the trie tree
	long int firstoffset=-1;	//Location of the first occurrence of a word in a text file
	long int nrofoccurrences=-1;  //The number of occurrences of a word in a text file
	int line=-1;

};

class triedoc
{
public:
	triedoc();
	triedoc(string pathname, string SitePath, int a);
	triedoc(string pathname, string dname,char c='c');
	void putdoc(string, string, char c='c');
	bool hasStopFile(string path);
	void getdoc(string pathname, string destination = Directory::getCurrentPath());
	void del(string pathname, char code='l');
	void flush(string pathname);
	void idx(string pathname);
	string expsearch(string pathname, string searchexp);
	int expcount(string sitePathname, string searchexp);
	searchStruct counthWildCard(string pathname, string word, searchStruct offset);
	searchStruct count(string pathname, searchStruct & offset, int index);
	searchStruct searchWord(string pathname, string word);
	searchStruct searchWildCard(string pathname, string wildcard);
	~triedoc();
		void SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }
	string& GetLastErrorMessage() { return this->lastErrorMessage; }



	string docname;
	trienode trierootnode;
	char triebuff[10 * sizeof(trienode)];
	vector<trienode> trienodesarray;
	bool hasTrieFile;



	private:
	string lastErrorMessage;
};

