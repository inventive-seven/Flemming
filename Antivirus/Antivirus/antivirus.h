#ifndef ANTIVIRUS
#define ANTIVIRUS

//addiction list

#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include "yara.h"
#include <iomanip>
class Antivirus
{   
	bool isDirectoryExists(LPCWSTR directoryNameToCheck);

	bool isFileExists(LPCWSTR fileNameToCheck);

	LPCWSTR charToLpcwstr(const char* stringToConvert);

	enum PathTo{ PathToFolder, PathToFile, NotExist };

	/*return type of directory:file, folder,notexist */
	PathTo isPathToFile(const char* stringToCheck);

	/*open file stream*/
	void startLoging(std::ofstream &file);

	/*close file stream*/
	void endLoging(std::ofstream &file);
	
	/*write infected or not infected file*/
	void writeLog(const char* fileName, bool infected);
		
	/*out file for log's*/
	std::ofstream OutLog;

	void GetFoldersAndFilesList(std::string path,
		std::vector<std::string> &folders,
		std::vector<std::string> &files);

	class SignatureAnalyzer
	{
	public:
		SignatureAnalyzer();
		~SignatureAnalyzer();
		int Scanfile(const char *);
		char* SetLibrarry_file(char *);
	private:
		int ScanType;
		char *Librarry_file;
		int SetScanType(int);		
		friend int callback_function_forfile(int, void*, void*);
	};

	std::pair<std::vector<std::string>, std::vector<std::string>> SeeFilesFolders(const char*);

	std::string getFullNameFile(const std::string&, const char*)const;
	std::string getFullNameFolder(const std::string&, const char*)const;

	SignatureAnalyzer analiz;


public:

	Antivirus(){}
	~Antivirus(){}

	/*check exist path and give next instructions*/
	void ToScan(const char* inString);


	static void outMessageToUser(const std::string&);

	static bool isThisCommand(const std::string&, const char*);

	char* getCurrentDateAndTime(char* currentDateAndTimeStr);


	/*constants implementation*/
	
	const std::string helpArgumentString = "-help";

	const std::string checkArgumentString = "-check";

	const std::string checkSystemFoulderArgumentString = "-checksys";

	const std::string infoArgumentString = "-info";

	const std::string wrongArgumentsNumberErrorString = "Wrong number of arguments. Use " + helpArgumentString + " for information.\n";

	const std::string wrongArgumentsErrorString = "Wrong arguments. Use " + helpArgumentString + " for information.\n";

	const std::string helpOutputText = checkArgumentString + " <path> - check file or directory\n" + 
									   checkSystemFoulderArgumentString + " - check system directory\n" +
									   infoArgumentString + " - about program\n";

	const std::string infoOutputText = "Antivirus ver. 0.0.1\n"
									   "AMCP SPBU 2015\n";

	const std::string checkNoPathErrorText = "Please type path to file or directory to check.\n";

};
#endif

