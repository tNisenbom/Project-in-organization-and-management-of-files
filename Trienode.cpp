#pragma once
#include "trienode.h"



//constractor of trienode
trienode::trienode()
{
	for (int i = 0; i < 27; i++)
		links[i] = -1;

	firstoffset = NULL;
	letter = NULL;
	nodeserialnr = NULL;
	nrofoccurrences = NULL;
	wordend = false;


}

trienode::trienode(long int n, long int f, long int nr, int nl, unsigned char l, bool w)
{

	nodeserialnr = n;
	firstoffset = f;
	nrofoccurrences = nr;
	letter = l;
	wordend = w;
	line = nl;

	for (int i = 0; i < 27; i++)
		links[i] = -1;
}

void trienode::clear()
{
	for (int i = 0; i < 27; i++)
		links[i] = -1;

	firstoffset = NULL;
	letter = NULL;
	nodeserialnr = NULL;
	nrofoccurrences = NULL;
	wordend = false;
}
trienode::~trienode(void)
{
}
