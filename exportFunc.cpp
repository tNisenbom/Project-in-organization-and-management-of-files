#include "Triesite.h"

extern "C"
{
	struct StringArray
	{
	public:
		int size;
		char** arr;
	};

	// for string and List<string>
	__declspec(dllexport) void  deleteCharPointer(char*& charPointer)
	{
		if (charPointer != NULL)
		{
			delete[] charPointer;
			charPointer = NULL;
		}
	}
	__declspec(dllexport) void  deleteStringArray(StringArray& stringArray)
	{
		if (stringArray.arr != NULL)
		{
			for (int i = 0; i < stringArray.size; i++)
				deleteCharPointer(stringArray.arr[i]);
			delete[] stringArray.arr;
			stringArray.arr = NULL;
		}
	}
	void  convertStringArray(StringArray& destStringArray, list<string>& sourceList)
	{

		destStringArray.size = sourceList.size();
		deleteStringArray(destStringArray);
		destStringArray.arr = new char*[destStringArray.size];

		list<string>::iterator it;
		int i = 0;
		for (it = sourceList.begin(); it != sourceList.end(); it++)
		{
			int length = (*it).length();
			destStringArray.arr[i] = new char[length + 1];
			strcpy(destStringArray.arr[i], (*it).c_str());
			i++;
		}
	}

	// for create Triesite cpp object pointer
	__declspec(dllexport) Triesite* makeTriesiteObjectDefault()
	{
		return new Triesite();
	}
	__declspec(dllexport) Triesite* makeTriesiteObject(char* siteName, char x, char y = 'q')
	{
		return new Triesite(siteName, x, y);
	}
	__declspec(dllexport) void deleteTriesiteObject(Triesite*& ThisPointer)
	{
		if (ThisPointer != NULL)
			delete  ThisPointer;
		ThisPointer = NULL;
	}
	__declspec(dllexport) const char* getLastTriesiteErrorMessage(Triesite* ThisPointer)
	{
		const char* str = ThisPointer->GetLastErrorMessage().c_str();
		return str;
	}

	// step 1
	__declspec(dllexport) void CreateSite(Triesite* thisPointer, char* siteName)
	{
		try
		{
			thisPointer->create(siteName);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void MountSite(Triesite* thisPointer, char* siteName, char Q_M)
	{
		try
		{
			thisPointer->mount(siteName, Q_M);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void UnmountSite(Triesite* thisPointer)
	{
		try
		{
			thisPointer->unmount();
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void PutStopFlSite(Triesite* thisPointer, char* stopeName) {
		try
		{
			thisPointer->putstopfl(stopeName);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	// step 2
	__declspec(dllexport) void DocUploadSite(Triesite* thisPointer, char* doc, char C_M)
	{
		try
		{
			thisPointer->docupload(doc, C_M);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void DocdownloadSite(Triesite* thisPointer, char* docName, char* newLocation)
	{
		try
		{
			thisPointer->docdownload(docName, newLocation);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void DelDocOfSite(Triesite* thisPointer, char* docName, char lORp) {
		try
		{
			thisPointer->docdel(docName, lORp);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void DelSite(Triesite* thisPointer, char lORp) {
		try
		{
			thisPointer->del(lORp);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	//step 3
	__declspec(dllexport) StringArray& GetDocNameList(Triesite* thisPointer, StringArray& stringArray, int code)
	{
		try
		{
			list<string> docList = thisPointer->listdoc(code);
			convertStringArray(stringArray, docList);
			return stringArray;

		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) void DocIdxSite(Triesite* thisPointer, char* docName) {
		try
		{
			thisPointer->docidx(docName);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}

	//step 4
	__declspec(dllexport) char*& ExpSearchSite(Triesite* thisPointer, char*& result, char* docName, char* expressionSearch)
	{
		try
		{
			string str = thisPointer->expsearch(docName, expressionSearch);
			result = new char[str.length() + 1];

			for (int i = 0; i < str.length(); i++)
				result[i] = str[i];

			result[str.length()] = 0;
			return result;

		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) int ExpCountSite(Triesite* thisPointer, char* docName, char* expressionSearch)
	{
		try
		{
			return thisPointer->expcount(docName, expressionSearch);
		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	__declspec(dllexport) StringArray& DocLookupSearchList(Triesite* thisPointer, StringArray& stringArray, char* expressionSearch)
	{
		try
		{
			list<string> docList = thisPointer->doclookup(expressionSearch);
			convertStringArray(stringArray, docList);
			return stringArray;

		}
		catch (exception ex)
		{
			thisPointer->SetLastErrorMessage(ex.what());
			throw ex;
		}
	}
	//__declspec(dllexport) int GetNumSearches(Triesite* thisPointer, char* docName)
	//{
	//	try
	//	{
	//		return thisPointer->getnumofsearches(docName);
	//	}
	//	catch (exception ex)
	//	{
	//		thisPointer->SetLastErrorMessage(ex.what());
	//		throw ex;
	//	}
	//}

}

