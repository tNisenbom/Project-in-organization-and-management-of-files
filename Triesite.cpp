#pragma once
#include "Triesite.h"
#include <string>
#ifndef Directory.h
#include "Directory.h"
#endif // !Directory.h
#ifndef triedoc.h
#include "triedoc.h"
#endif // !triedoc.h

//default constructor
Triesite::Triesite()
{
	sitename = "";
	mounted = false;
	mountype = NULL;
}

//constructor
//create or open the folder
Triesite::Triesite(std::string name, char code, char optional)
{
	try
	{
		if (name.find_first_of('\\')/*==true*/)
			sitename = name;
		else
			sitename = Directory::getCurrentPath() + '\\' + name;
		if (code == 'c' || code == 'C')
			create(sitename);
		else
			if (code == 'm' || code == 'M')
			{
				mounted = false;
				mount(sitename, code);
			}
	}
	catch (char* msg)
	{
		throw msg;
	}

}

//a function that create a site
//fullPathName-the path+the name of the new site
void Triesite::create(string fullPathName)
{
	try
	{
		if (fullPathName.find_first_of('\\'))
			sitename = fullPathName;
		else
			sitename = Directory::getCurrentPath() + '\\' + fullPathName;
		if (Directory::dirExists(fullPathName))
			throw "this directory is already exist";
		Directory::createDirectory(fullPathName);//creates a new directory
		mounted = false;
		//sitename = fullPathName;

	}
	catch (char* msg)
	{
		throw msg;
	}
}

//a function that open an exist folder
//path-the path of the site
//c-create or mount
void Triesite::mount(string path, char c)
{
	try
	{
		if (!Directory::dirExists(path))
			throw "the directory doesn't exist";
		if (mounted)
			throw"this site is already mounted";
		if (c == 'q' || c == 'Q') //sets value of mountype according to code 
			mountype = 'q';
		else if (c == 'm' || c == 'M')
			mountype = 'm';
		else throw "code has to be either m or q\n";
		list<string> DList = Directory::getSubDirectoryNameList(path); //gets a list of the files in directory
		list<string>::iterator it1 = DList.begin(); //scans list of folders
		for (; it1 != DList.end(); it1++)
		{
			triedoc newDoc((*it1), path, 2);
			doclist.push_back(newDoc);
		}
		mounted = true;
	}
	catch (char* msg)
	{
		throw msg;
	}

}

//a function that close the Triesite
void Triesite::unmount()
{
	try
	{

		mounted = false;
		doclist.clear();
	}
	catch (char* msg)
	{
		throw msg;
	}
}

//a function that put a stoplist file
//stopname-the path of the stop file 
void Triesite::putstopfl(string stopname)
{
	try
	{
		if (mounted == false)
			throw "the site is not opened\n";
		if (mountype == 'q' || mountype == 'Q')
			throw "the site was opened only for queries\n";
		if (stopname.find("\\") == NULL)
			stopname = Directory::getCurrentPath() + "\\" + stopname;
		list<string> fileList = Directory::getFileNameList(sitename); //gets a list of the files in the directory
		list<string>::iterator it1 = fileList.begin(); //scans list of folders
		for (; it1 != fileList.end(); it1++)	//look if stop file is exist
		{
			if (Directory::getFileSuffix(*(it1)) == "lst")
			{
				Directory::removeFile(*it1);
				break;
			}

		}
		string onlyPath = stopname.substr(0, stopname.length() - Directory::getFileName(stopname).length() - 1);
		list<string> fileList1 = Directory::getFileNameList(onlyPath); //gets a list of the files in the directory
		list<string>::iterator it = fileList1.begin(); //scans list of folders
		bool find = false;
		string name1 = Directory::getFileName(stopname);
		for (; it != fileList1.end(); it++)	//look if stop file is exist
		{
			if ((*(it)) == name1)
			{
				find = true;
				break;
			}

		}
		if (!find)
		{
			throw "the source file doesnt exist\n";
		}
		//copies the stop file to the site as "stop.lst" file
		Directory::copyFileToDirectory(stopname, sitename, false, "stop.lst");

	}
	catch (char* msg)
	{
		throw msg;
	}

}

//a function that look if the folder alredy exist
//name-the name of the doc
//the func' return pointer to the doc in the doc list
triedoc* Triesite::docexists(string name)
{
	try
	{
		list<triedoc>::iterator it1 = doclist.begin(); //scans list of folders
		for (; it1 != doclist.end(); it1++)
			if (it1->docname == Directory::getFilePrefix(Directory::getFileName(name)))
				return &(*it1);
		return NULL;
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//a function that load a file to the site
//filename-the path of the doc that the func' enter to the site
//code-copy or move
void Triesite::docupload(string filename, char code)
{
	try
	{

		string onlyFileName = Directory::getFilePrefix(Directory::getFileName(filename));
		triedoc* docExist = docexists(onlyFileName);
		if (docExist != NULL)
			if (docExist->hasTrieFile == true)
				throw "this doc already exists in the site\n";
			else docExist->del(sitename + "\\" + onlyFileName, 'p');	//if it already exist a file with same name but deleted logic, delete the file physical
			triedoc newDoc(sitename, filename, code);	//enter the file to the site with putdoc
			doclist.push_back(newDoc);	//enter the file logic
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//a functions copies a file from the directory to the given location.
///fileName-the name of the file
//destination-the path of the destination
//the func' return the end dest' of rhe doc
string Triesite::docdownload(string fileName, string destination)
{
	triedoc* doc = docexists(fileName);
	string fileName1 = Directory::getFileName(fileName);
	if (doc == NULL)
		throw "the source document dosen't exist!\n";
	string destinationDirectory = destination + "\\" + fileName1;
	doc->getdoc(sitename, destinationDirectory);
	return destinationDirectory;

}

//a function that delete file from the site
//filename-the path of the file that the func' delete
//code-logi' or phicical
void Triesite::docdel(string filename, char code)
{
	try
	{
		triedoc* docToDelete = docexists(filename);
		if (docToDelete == NULL)
			throw "this doc doesn't exist in the site\n";
		string f = sitename + '\\' + filename;
		(*docToDelete).del(f, code);
		if (code == 'P' || code == 'p')
		{
			list<triedoc>::iterator it1 = doclist.begin(); //scans list of folders
			for (; it1 != doclist.end(); it1++)
				if (it1->docname == Directory::getFilePrefix(Directory::getFileName(filename)))
					doclist.erase((it1));
		}
	}
	catch (char* ex)
	{
		throw ex;
	}


}


//a function that delete the whole site
//code-logi' or phicical
void Triesite::del(char code)
{
	try
	{
		if (code == 'P' || code == 'p')
		{
			if (mounted == true)
				throw "cannot delete the site when it's mounted\n";
			doclist.clear();
			Directory::DeleteDirectory(sitename);
			sitename = "";
			mounted = false;
			return;
		}
		list<triedoc>::iterator it = doclist.begin();
		for (; it != doclist.end(); it++)
			it->del(sitename + "\\" + (*it).docname, 'l');

	}
	catch (char* ex)
	{
		throw ex;
	}
}


//a function that return a list of files:  0-all the files,1-the indexed files, 2-the not indexed files
list<string> Triesite::listdoc(int choice)
{
	try
	{
		list<string> listdoc;
		list<triedoc>::iterator it;
		switch (choice)
		{
			//gets list of all files, indexed and not indexed. indexed ones get ** appended to their name
		case 0:for (it = doclist.begin(); it != doclist.end(); it++)
		{
			if ((*it).hasTrieFile)
				listdoc.push_back(it->docname + "**");
			else listdoc.push_back(it->docname);
		}
			   break;
			   //gets list of only indexed files
		case 1:for (it = doclist.begin(); it != doclist.end(); it++)
		{
			if ((*it).hasTrieFile)
				listdoc.push_back(it->docname);
		}
			   break;
			   //gets list of only not indexed files
		case 2:for (it = doclist.begin(); it != doclist.end(); it++)
		{
			if (!(*it).hasTrieFile)
				listdoc.push_back(it->docname);
		}
			   break;
		default:throw "wrong choice";
		}
		return listdoc;
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//a function that get a file and induxes it
//docName-the name of the doc without sofix
void Triesite::docidx(string docName)
{
	try
	{
		string onlyFileName = Directory::getFilePrefix(Directory::getFileName(docName));
		triedoc* docExist = docexists(onlyFileName);	//check if the doc exist and save it
		if (docExist == NULL)
			throw "this doc doesn't exists in the site\n";
		docExist->idx(sitename);
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//a function that search an exp' in the doc
//pathname-the path of the doc
//searchexp-the expretion that we look for it
//return the line in the text that the word appear there
string Triesite::expsearch(string pathname, string searchexp)
{
	try
	{
		string onlyFileName = Directory::getFilePrefix(Directory::getFileName(pathname));
		if (!docexists(onlyFileName))
			throw "this doc doesn't exist in the site\n";
		return (docexists(onlyFileName))->expsearch(sitename, searchexp);
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//This function gets an expression with words and returns the sum of the occurences all words found
//pathname-the path of the doc
//countexp-the expretion that we look for it
//return how much time  the word appear in the text 
int Triesite::expcount(string pathname, string countexp)
{
	try
	{
		string onlyFileName = Directory::getFilePrefix(Directory::getFileName(pathname));
		if (!docexists(onlyFileName))
			throw "this doc doesn't exist in the site\n";
		return (docexists(onlyFileName))->expcount(sitename, countexp);
	}
	catch (char* ex)
	{
		throw ex;
	}
}

//This function gets an expression with words and can include | and & 
// and returns a list of files which include this expression.
list<string> Triesite::doclookup(string expression)
{
	try
	{
		list<string> listdoc;
		list<triedoc>::iterator it;
		for (it = doclist.begin(); it != doclist.end(); it++)
			if (it->expsearch(sitename, expression) != "")
				listdoc.push_back(it->docname);
		return listdoc;
	}
	catch (char* ex)
	{
		throw ex;
	}
}

Triesite::~Triesite()
{
}
