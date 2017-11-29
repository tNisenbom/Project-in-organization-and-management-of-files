#pragma once
#include "triedoc.h"
#include <string>
#include "Directory.h"
#include <algorithm>  
#include <iterator>
#include <vector>

triedoc::triedoc()
{
	docname = "";
	hasTrieFile = false;
}

triedoc::triedoc(string pathname, string SitePath, int a)
{
	docname = pathname;
	string fullPath = SitePath + '\\' + pathname;
	list<string> lst = Directory::getFileNameList(fullPath);
	list<string>::iterator it = lst.begin();
	for (; it != lst.end(); it++)
	{
		if (Directory::getFileSuffix((*it)) == "trie")
		{
			hasTrieFile = true;
			return;
		}
	}
	hasTrieFile = false;
}


triedoc::triedoc(string pathname, string dname, char c)
{
	docname = dname;
	hasTrieFile = false;
	putdoc(pathname, dname, c);

}

//a function that add file to the site without indux
//pathname-the path of the site
//filename-the path of the file that the function copy (with suffix)
//code-c/m-copy or move
void triedoc::putdoc(string pathname, string filename, char code)
{
	try
	{
		docname = Directory::getFilePrefix(Directory::getFileName(filename));
		bool txtFound = false;
		bool stopFileExists = false;
		string DocFolder = pathname + "\\" + docname;		//appends the name of folder to the directory
		if (filename.find("\\") == NULL)			//if the filename has no path to it, a path to the currendirectory will be added to it
			filename = Directory::getCurrentPath() + "\\" + filename;
		string onlyPath = filename.substr(0, filename.length() - Directory::getFileName(filename).length() - 1); //gets location of original file
		list<string> sourceFileList = Directory::getFileNameList(onlyPath);		//gets list of all the files in the original location.
		list<string>::iterator it = sourceFileList.begin();
		for (it = sourceFileList.begin(); it != sourceFileList.end(); it++)		//checks if txt and stop files exist in original location
		{
			if ((*it) == docname + ".stop")		//stopfile found
				stopFileExists = true;
			if ((*it) == docname + ".txt")		//txtfile found
				txtFound = true;
		}
		if (txtFound == false)//txtfile not found at all
			throw exception("this doc doesn't exist at all");
		string  StopDoc = Directory::getFilePrefix(filename) + ".stop";//new destination for stopfile, total path included
		string  TextDoc = Directory::getFilePrefix(filename) + ".txt";//new destination for txtfile,in case filename was entered without suffix
		if (Directory::dirExists(DocFolder))
			throw exception("this doc is already exist");
		Directory::createDirectory(DocFolder);//creates the new folder
											  //move the files
		if (code == 'm' || code == 'M')
		{
			Directory::moveFileToDirectory(TextDoc, DocFolder);
			if (stopFileExists == true)
				Directory::moveFileToDirectory(StopDoc, DocFolder);
		}
		//copy the files
		else if (code == 'c' || code == 'C')
		{
			Directory::copyFileToDirectory(TextDoc, DocFolder, false);
			if (stopFileExists == true)
				Directory::copyFileToDirectory(StopDoc, DocFolder, false);
		}
		else throw exception("the third parameter has to be m or c");
		//if stopfile was not found in original location, checking if main site has a global stop file
		if (stopFileExists == false)
		{
			list<string> destDirFileList = Directory::getFileNameList(pathname);
			for (it = destDirFileList.begin(); it != destDirFileList.end(); it++)
			{
				//global stop file found, so copy the stop file from the site
				if ((*it) == "stop.lst")
				{
					Directory::copyFileToDirectory(pathname + '\\' + "stop.lst", DocFolder, false, Directory::getFileName(DocFolder) + ".stop");
					stopFileExists = true;
					break;
				}
			}
			//otherwise create emtpy binary file in "directory\docname\docname.stop"
			if (stopFileExists == false)
			{
				stopFileExists = true;
				fstream f;
				string file1;

				file1 = DocFolder;
				file1.append("\\" + docname + ".stop");
				f.open(file1, ios::binary | ios::out);
				f.close();
			}
		}
	}
	catch (char* ex)
	{
		//throw ex;
		throw ex;
	}

}

//a function that checks if the doc has stop file
bool triedoc::hasStopFile(string sitePath)
{
	string path = sitePath + '\\' + docname;
	list<string> sourceFileList = Directory::getFileNameList(path);		//gets list of all the files in the original location.
	list<string>::iterator it = sourceFileList.begin();
	for (it = sourceFileList.begin(); it != sourceFileList.end(); it++)		//checks if txt and stop files exist in original location
	{
		if ((*it) == docname + ".stop")		//stopfile found
			return true;
	}
	return false;
}

//a function that copy a file from the site to another directory
void triedoc::getdoc(string pathname, string destination)
{
	try
	{
		//		string path = Directory::getFilePrefix(pathname);	//in case path was entered with suffix, this line takes it off
		bool docFound = false;
		list<string> dirFileList = Directory::getSubDirectoryNameList(pathname);//gets list of subfiles in directory
		list<string>::iterator it = dirFileList.begin();
		//checks if file to be copied exists
		for (; it != dirFileList.end(); it++)
		{
			if ((*it) == docname)
			{
				docFound = true;
				break;
			}
		}
		if (docFound == false)
			throw exception("doc not found");
		if (Directory::dirExists(destination))
			throw exception("this doc is already exist");
		Directory::createDirectory(destination);
		//Directory::copyFileToDirectory(path + "\\" + docname + "\\" + docname + ".txt", destination, false);
		string pathDoc = pathname + "\\" + Directory::getFileName(docname);
		list<string> ll = Directory::getFileNameList(pathDoc);
		list<string>::iterator it1 = ll.begin();
		for (; it1 != ll.end(); it1++)
		{
			Directory::copyFileToDirectory(pathDoc + "\\" + (*it1), destination, false);
		}
	}

	catch (char* ex)
	{
		throw ex;
	}

}

//a function that delete a doc
//sitePathName-the path of the site
void triedoc::del(string pathname, char code)
{
	try
	{
		string path = Directory::getFilePrefix(pathname);//in case path was entered with suffix, this line takes it off
		if (code == 'P' || code == 'p')// delete phisical the folder from the directory
		{
			bool check = Directory::DeleteDirectory(path);//removes the folder itself

														  //Directory::DeleteDirectory(path); //deletes the subFolders

														  //initializes all the fields of the triedoc
			docname = "";
			trierootnode.clear();
			trienodesarray.clear();
			hasTrieFile = false;
			return;
		}
		if (code == 'L' || code == 'l')// delete the folder only logically from the directory
		{
			list<string> docFileList = Directory::getFileNameList(path);//gets list of files in subfolder
			list<string>::iterator it1 = docFileList.begin();
			//checks to see it the trie file exists
			for (; it1 != docFileList.end(); it1++)
				//if trie file was found, deletes it
				if (*it1 == docname + ".trie")
				{
					Directory::removeFile(path + "\\" + (*it1));
					trierootnode.clear();
					trienodesarray.clear();
					hasTrieFile = false;
					return;
				}


		}
		else throw exception("wrong code, code should be either p or l");
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//a function that make trie file
//pathname-the path of the site
void triedoc::flush(string pathname)
{
	try
	{
		if (Directory::dirExists(pathname + '\\' + docname) == NULL)
			throw exception("the file is not exist");
		if (hasTrieFile == true)
			throw exception("trie file is alredy exist");
		//opens a trie file
		fstream  trieFile(pathname + "\\" + docname + "\\" + docname + ".trie", ios::out | ios::binary);
		if (trieFile.is_open())
		{
			if (trienodesarray.size() == 0)
				throw exception("trienodes array is empty");
			int a = trienodesarray.size() / 10;//number of groups of 10 trienodes in array
			for (int i = 0; i < a; i++)//copy group by group to buffer
			{
				memcpy(&triebuff[0], &trienodesarray[i * 10], 10 * sizeof(trienode));//load buffer
				int pos = i * 10 * sizeof(trienode);	//the position in the binary file
				trieFile.seekp(pos);
				trieFile.write((char*)&triebuff, 10 * sizeof(trienode));	//write to file
			}
			hasTrieFile = true;
			//copy leftover trienodes
			int j = trienodesarray.size() % 10;
			if (j)
			{
				memcpy(&triebuff[0], &trienodesarray[a * 10], j * sizeof(trienode));//load buffer
				int pos = a * 10 * sizeof(trienode);	//the position in the binary file
				trieFile.seekp(pos);
				trieFile.write((char*)&triebuff, j * sizeof(trienode));	//write to file
			}
		}
		else
		{
			trieFile.close();
			throw exception("file is not open for writing");
		}
		trieFile.close();
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//a function that indexd the text file
//sitePathName-the path of the site
void triedoc::idx(string sitePathName)
{
	try
	{
		string docNameWithSuffix;
		string fullFolder = sitePathName + "\\" + docname;						//the path of the doc
		list<string> lst = Directory::getFileNameList(fullFolder);			//gets list of files in this doc
		list<string>::iterator it = lst.begin();

		//finds the text file abd check if the doc dont indexted already
		for (; it != lst.end(); it++)
		{

			if (Directory::getFileSuffix(*it) == "trie")					 //if the doc has alredy a trie file throw exception
				throw exception("File is already indexed!");
			if (Directory::getFileSuffix(*it) != "stop")	//if not a stop file (and not a trie) than it must be the text file
			{
				docNameWithSuffix = *it;
				break;
			}
		}

		if (it == lst.end())
			throw exception("There is no text file to index!");

		string s;
		fstream stopFile;
		if (hasStopFile(sitePathName) == true)
			stopFile.open(sitePathName + "\\" + docname + "\\" + docname + ".stop", ios::in);// open the stop file
		else stopFile.open(sitePathName + "\\" + "stop.lst", ios::in);// if the doc doesn't have a stop file, open the stop file of the site
		if (!stopFile.is_open())   //if not succeed to open the stop file
			throw exception("stopFile is not open");
		vector<string> stopWords;
		//puts all the words of the stopfile in vector 
		while (!stopFile.eof())
		{
			stopFile >> s;		//enter a word from the stop file to s 
			stopWords.push_back(s);		//puts s in the vector
		}

		//opens a txt file
		fstream  txtFile(sitePathName + "\\" + docname + "\\" + docNameWithSuffix, ios::in);
		if (txtFile.is_open())
		{
			list<string> stringList;
			char* word;
			char* line;
			line = new char[1024];
			int numLine = 0;
			long int serialnumber = 1, offset = 0;

			trienodesarray.push_back(trienode());		//save a place for the root

														//index line after line
			do
			{
				txtFile.getline(line, 1024, '\n');	//take a line from the txtfile till it found '\n' and put it in line
				stringList = Directory::getWordsList((string)line, "?,!. *#");	//put in stringList a list of words without ?,!. *#
				list<string>::iterator it = stringList.begin();
				for (it; it != stringList.end(); it++) //index word after word
				{
					int k = 0;
					s = *it;	// s is a word from the txtfile that now we indexed it
					for (int t = 0; t < s.length(); t++)	//convert the word to caps letters
						s[t] = toupper(s[t]);
					word = new char[s.length() + 1];
					for (k; k < s.length(); k++)	//move the from string to char
						word[k] = (char)s[k];
					word[k] = '\0';
					int len = strlen(word);
					bool foundInStop = false;      //if the word was found in the stopfile,skip it and don't index it
					for (int i = 0; i < stopWords.size(); i++)//over on the stopWords vector and check if s exist there
						if (Directory::epualString(s, stopWords[i]))
						{
							foundInStop = true;
							break;
						}
					if (!foundInStop)	//the word is not found in the stop file, so we index it
					{
						int i = 0, j1;
						//bool finished = false;
						int j = trierootnode.links[word[i] - 'A'];	//j is the place of the current letter in the links
						j1 = j;		//j1 is the place of the last indexed letter
									//if first letter of the word has already indexed 
									/*if (j != -1)
									{*/
									//i++;	//move to the next letter in the word till it already not find indexed letter
						while (j != -1 && word[i] != '\0' /*&& trienodesarray[j].links[word[i] - 'A'] != -1*/)
						{
							j1 = j;
							i++;
							j = trienodesarray[j].links[word[i] - 'A'];
						}
						//entire word has already indexed - the word is already exist
						if (word[i] == '\0')
						{
							trienodesarray[j1].nrofoccurrences++;
							if (!trienodesarray[j1].wordend)
							{
								trienodesarray[j1].wordend = true;
								trienodesarray[j1].firstoffset = offset;
							}

							//	offset--;	//if the word already exist not add 1 to the offset 
							//finished = true;
						}
						else
						{
							while (word[i + 1] != '\0')	//index the letters that leave in thw word without the last letter
							{
								trienode node(serialnumber, offset, 0, numLine, word[i], false);
								if (j1 != -1)
									trienodesarray[j1].links[word[i] - 'A'] = serialnumber;
								else
									trierootnode.links[word[i] - 'A'] = serialnumber;
								//j1 = j;
								j1 = serialnumber++;
								trienodesarray.push_back(node);//?????????????????????put at the end?
								i++;
							}
							//index the last letter
							trienode node(serialnumber, offset, 1, numLine, word[i], true);
							trienodesarray[j1].links[word[i] - 'A'] = serialnumber;
							serialnumber++;
							trienodesarray.push_back(node);
						}
					}
					offset++;
				}
				numLine++;
			} while (!txtFile.eof());
			trienodesarray[0] = trierootnode;
			flush(sitePathName);
			trienodesarray.clear();
			//////////////////////////////////////////////////////////////////////////	delete word, line;
		}
		else throw exception("cannot open text file");
		txtFile.close();
		stopFile.close();

	}
	catch (char* ex)
	{
		throw ex;
	}
}



//This function gets an expression with words and can include | and & 
// and returns the line in which the first word found appears.
//sitePathname-the path of the doc
//searchexp-the expretion that we look for it
string triedoc::expsearch(string sitePathname, string searchexp)
{
	try
	{
		fstream  txtFile(sitePathname + "\\" + docname + "\\" + docname + ".txt", ios::in);//opens the text file
		if (!txtFile.is_open())
			throw exception("couldn't open txtfile");
		list<string> wordList;
		list<string> wordList1;
		searchStruct offset;
		char *line;


		line = new char[1024];
		bool logicalSigns = false;
		for (int i = 0; searchexp[i] != '\0'; i++)//check to see if there are logical signs in the expression
		{
			if (searchexp[i] == '&')
			{
				logicalSigns = true;
				break;
			}
		}
		if (!logicalSigns)//if none were found, then we search for the offset of the first word found in the searchexp
		{

			long int minLine = -1;
			wordList = Directory::getWordsList(searchexp, " |");
			list<string>::iterator it = wordList.begin();
			for (it; it != wordList.end(); it++)
			{
				if ((*it)[(*it).size() - 1] != '*')//check if it's not a wildcard
					offset = searchWord(sitePathname, (*it));
				else offset = searchWildCard(sitePathname, (*it));//the word is wildcard
				if ((offset.line < minLine && offset.firstoffset != -1) || (minLine == -1))//the word found
					minLine = offset.line;
			}

			if (minLine == -1)
			{
				return "";//if thr exp' not found return ""
			}
			for (int i = 0; i <= minLine; i++)
				txtFile.getline(line, 1024, '\n');
			string sLine = line;
			delete line;
			txtFile.close();
			return sLine;
		}
		else       //if there are logical signs
		{
			int len, len1 = 0;
			long int minLine = -1, minimum = -1;
			wordList1 = Directory::getWordsList(searchexp, "&");
			list<string>::iterator it1 = wordList1.begin();
			for (; it1 != wordList1.end(); it1++)
			{
				bool found = false;
				wordList = Directory::getWordsList((*it1), "| ");
				len = wordList.size();
				list<string>::iterator it = wordList.begin();
				for (it; it != wordList.end(); it++)
				{
					if ((*it)[(*it).size() - 1] != '*')//check if it's not a wildcard
						offset = searchWord(sitePathname, (*it));
					else offset = searchWildCard(sitePathname, (*it));//the word is wildcard
					if ((offset.line < minLine && offset.firstoffset != -1) || (minLine == -1))//the word found
						minLine = offset.line;
					if (offset.line != -1)
						found = true;
				}

				if (found == false/*|| len!=len1*/)
					return "";//if thr exp' not found return ""
				if (minLine < minimum || minimum == -1)
					minimum = minLine;

			}
			for (int i = 0; i <= minimum; i++)
				txtFile.getline(line, 1024, '\n');
			string sLine = line;
			delete line;
			txtFile.close();
			return sLine;

		}

	}
	catch (char* ex)
	{
		throw ex;
	}
}


//This function gets an expression with words and can include | and & 
// and returns how much time the word found in the text.
//sitePathname-the path of the site
//searchexp-the expretion that we look for it
int triedoc::expcount(string sitePathname, string searchexp)
{
	try
	{
		fstream  txtFile(sitePathname + "\\" + docname + "\\" + docname + ".txt", ios::in);//opens the text file
		if (!txtFile.is_open())
			throw exception("couldn't open txtfile");
		list<string> wordList;
		list<string> wordList1;
		searchStruct offset;
		char *line;

		line = new char[1024];
		bool logicalSigns = false;
		for (int i = 0; searchexp[i] != '\0'; i++)//check to see if there are logical signs in the expression
		{
			if (searchexp[i] == '&')
			{
				logicalSigns = true;
				break;
			}
		}
		if (!logicalSigns)//if none were found, then we search for the offset of the first word found in the searchexp
		{
			long int minO = -1, minA = -1;
			wordList = Directory::getWordsList(searchexp, " |");
			list<string>::iterator it = wordList.begin();
			for (it; it != wordList.end(); it++)
			{
				if ((*it)[(*it).size() - 1] != '*')//check if it's not a wildcard
					offset = searchWord(sitePathname, (*it));
				else offset = counthWildCard(sitePathname, (*it), offset);//the word is wildcard
				if ((offset.firstoffset < minO && offset.firstoffset != -1) || (minO == -1))//the word found
				{
					minO = offset.firstoffset;
					minA = offset.nrofoccurrences;
				}
			}

			if (minO == -1)
			{
				return 0;//if thr exp' not found return 0
			}
			return (int)minA;
		}
		else       //if there are logical signs
		{
			long int minO = -1, minA = -1, minimum = -1;
			wordList1 = Directory::getWordsList(searchexp, "&");
			list<string>::iterator it1 = wordList1.begin();
			for (; it1 != wordList1.end(); it1++)
			{

				wordList = Directory::getWordsList((*it1), " |");
				list<string>::iterator it = wordList.begin();
				for (it; it != wordList.end(); it++)
				{
					if ((*it)[(*it).size() - 1] != '*')//check if it's not a wildcard
						offset = searchWord(sitePathname, (*it));
					else offset = counthWildCard(sitePathname, (*it), offset);//the word is wildcard
					if ((offset.firstoffset < minO && offset.firstoffset != -1) || (minO == -1))//the word found
					{
						minO = offset.firstoffset;
						minA = offset.nrofoccurrences;
					}
				}

				if (minO == -1)
					return 0;//if thr exp' not found return 0
				if (minO < minimum || minimum == -1)
					minimum = minO;
			}
			return minA;

		}

	}
	catch (char* ex)
	{
		throw ex;
	}
}

//This function gets an expression with words and include *
// and returns how much time the word found in the text.
//pathname-the path of the site
//wildcard-the expretion that we look for it
//offset-the details of the wildcard
//return the offset
searchStruct triedoc::counthWildCard(string pathname, string wildcard, searchStruct offset)
{
	try
	{
		trienode tnode;
		searchStruct offset;
		for (int i = 0; i < wildcard.length() - 1; i++)
			wildcard[i] = toupper(wildcard[i]);
		fstream  trieFile(pathname + "\\" + docname + "\\" + docname + ".trie", ios::in | ios::binary);//opens trie file
		if (trieFile.is_open())
		{
			trieFile.seekg(0);
			trieFile.read((char*)& trierootnode, sizeof(trienode)); //reads the trie root node from the TrieFile 


			int i = 0, j = trierootnode.links[wildcard[i] - 'A'];
			if (j == -1)//root is not pointing to the first letter of the word
				return offset;

			while (wildcard[i] != '*' && j != -1)
			{
				trieFile.seekg(sizeof(trienode)*j);
				trieFile.read((char*)& tnode, sizeof(trienode)); //reads  node from the TrieFile 
				j = tnode.links[wildcard[++i] - 'A'];
			}

			return count(pathname, offset, tnode.nodeserialnr);

		}
		else throw exception("cannot open trie file");
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//a function that count how mach time a word in the text file
//pathname-the path of the site
//offset-the offset of the word
//index-the serial number of the node that the function work on her
searchStruct triedoc::count(string pathname, searchStruct &offset, int index)
{
	try
	{
		trienode tnode;
		fstream  trieFile(pathname + "\\" + docname + "\\" + docname + ".trie", ios::in | ios::binary);//opens trie file

		trieFile.seekg(sizeof(trienode)*index);
		trieFile.read((char*)& tnode, sizeof(trienode));	//read the node into tnode


		for (int i = 0; i < 27; i++)	//go on the links and check
		{
			if (tnode.links[i] != -1)
				count(pathname, offset, tnode.links[i]);// .nrofoccurrences;
		}

		if (tnode.wordend == true)
		{
			if (tnode.firstoffset < offset.firstoffset)
			{
				offset.firstoffset = tnode.firstoffset;
				offset.line = tnode.line;

			}
			if (offset.firstoffset == -1)
			{
				offset.firstoffset = tnode.firstoffset;
				offset.line = tnode.line;
				offset.nrofoccurrences++;
			}
			offset.nrofoccurrences++;
		}
		return offset;
	}
	catch (char* a)
	{
		throw a;
	}
}


//This function gets an expression with word 
// and returns offset-the details of the word.
searchStruct triedoc::searchWord(string pathname, string word)
{
	try
	{
		trienode tnode;
		searchStruct offset;
		for (int i = 0; i < word.length(); i++)
			word[i] = toupper(word[i]);

		fstream  trieFile(pathname + "\\" + docname + "\\" + docname + ".trie", ios::in | ios::binary);//opens trie file
		trieFile.seekg(0);
		trieFile.read((char*)& trierootnode, sizeof(trienode)); //reads the trie root node from the TrieFile 

		if (trieFile.is_open())
		{
			int i = 0, j = trierootnode.links[word[i] - 'A'];
			if (j == -1)//root is not pointing to the first letter of the word
				return offset;

			while (word[i] != '\0' && j != -1)
			{
				trieFile.seekg(sizeof(trienode)*j);
				trieFile.read((char*)& tnode, sizeof(trienode)); //reads  node from the TrieFile 
				j = tnode.links[word[++i] - 'A'];
			}
			if (tnode.letter == word[i - 1] && tnode.wordend == true)//if the last word equal to the last node
			{
				offset.firstoffset = tnode.firstoffset;
				offset.line = tnode.line;
				offset.nodeserialnr = tnode.nodeserialnr;
				offset.nrofoccurrences = tnode.nrofoccurrences;
			}
			return offset;
		}
		else throw exception("cannot open trie file");
	}
	catch (char* ex)
	{
		throw ex;
	}
}


//This function gets an expression with wildcard 
// and returns offset-the details of the word.
//pathname-the path of the siet
//wildcard-the exp' that the func' search
searchStruct triedoc::searchWildCard(string pathname, string wildcard)
{
	try
	{
		trienode tnode;
		searchStruct offset;
		for (int i = 0; i < wildcard.length() - 1; i++)
			wildcard[i] = toupper(wildcard[i]);
		fstream  trieFile(pathname + "\\" + docname + "\\" + docname + ".trie", ios::in | ios::binary);//opens trie file
		if (trieFile.is_open())
		{
			trieFile.seekg(0);
			trieFile.read((char*)& trierootnode, sizeof(trienode)); //reads the trie root node from the TrieFile 


			int i = 0, j = trierootnode.links[wildcard[i] - 'A'];
			if (j == -1)//root is not pointing to the first letter of the word
				return offset;


			while (wildcard[i] != '*' && j != -1)
			{
				trieFile.seekg(sizeof(trienode)*j);
				trieFile.read((char*)& tnode, sizeof(trienode)); //reads  node from the TrieFile 
				j = tnode.links[wildcard[++i] - 'A'];
			}
			i--;		//move to the last letter
			if (tnode.wordend == true)//if see that it's end word, save it.
			{
				offset.firstoffset = tnode.firstoffset;
				offset.line = tnode.line;
				offset.nodeserialnr = tnode.nodeserialnr;
				offset.nrofoccurrences = tnode.nrofoccurrences;
			}


			while (1)
			{
				int min = -1;
				for (int k = 0; k < 27; k++)
					if ((min == -1) || (tnode.links[k] < min && tnode.links[k] != -1))
						min = tnode.links[k];
				if (min == -1)
					return offset;
				trieFile.seekg(sizeof(trienode)*min);
				trieFile.read((char*)& tnode, sizeof(trienode));
				if ((tnode.wordend == true && tnode.firstoffset < offset.firstoffset) || (offset.firstoffset == -1))
					//if see that it's end word and its came in the file before the last offset, save it.
				{
					offset.firstoffset = tnode.firstoffset;
					offset.line = tnode.line;
					offset.nodeserialnr = tnode.nodeserialnr;
					offset.nrofoccurrences = tnode.nrofoccurrences;
				}
			}
		}
		else throw exception("cannot open trie file");
	}
	catch (char* ex)
	{
		throw ex;
	}
}

triedoc::~triedoc(void)
{
}
