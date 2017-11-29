using namespace std;
#pragma once
#ifndef string
#include <string>
#endif // !string
#ifndef list
#include <list>
#endif // !list
#ifndef vector
#include <vector>
#endif // !vector



class trienode
{
public:
	long int nodeserialnr; //Serial number of vertex array vertices of the trie tree
	long int firstoffset;	//Location of the first occurrence of a word in a text file
	long int nrofoccurrences;  //The number of occurrences of a word in a text file
	unsigned char letter;   //A character from 256 characters of the ASCII
	bool wordend;	//Is this character indicates the end of a word?
	int line;
	trienode();
	trienode(long int n, long int f, long int nr,int nl, unsigned char l, bool w);
	void clear();
	~trienode(void);


	long int links[27];
	
};
