using namespace std;
#pragma once
#include <string>
#include <iostream>
#include <list>
#include "triedoc.h"

class Triesite
{
public:
	Triesite();
	Triesite(std::string, char, char c='q');
	void create(string s);
	void mount(string path, char c='q');
	void unmount();
	void putstopfl(string stop);
	triedoc * docexists(string);
	void docupload(string, char);
	string docdownload(string fileName, string destination = Directory::getCurrentPath());
	void docdel(string filename, char code = 'l');
	void del(char code='l');
	list<string> listdoc(int choice=0);
	void docidx(string docName);
	string expsearch(string pathname, string searchexp);
	int expcount(string pathname, string countexp);
	list<string> doclookup(string expression);
	~Triesite();
	void SetLastErrorMessage(string lastErrorMessage) { this->lastErrorMessage = lastErrorMessage; }
	string& GetLastErrorMessage() { return this->lastErrorMessage; }

private:
	string lastErrorMessage;
	string sitename;	//full path name
	list<triedoc> doclist;	//list of all the document in the stock
	bool mounted;
	char mountype;
};

