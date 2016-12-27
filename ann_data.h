#ifndef ANN_DATA_H
#define ANN_DATA_H

#include <vector>
#include <iostream>
#include <string>
using std::string;
using std::vector;
using std::cout;
using std::endl;

#include <sys/types.h>
#include <dirent.h>


/**	class of the data for ann
 *	get the file from dir and get the vector from file
 *	Members:
 *		sampleInput: data vector of file
 *		targetLabel: real label of each data 	
 */
class AnnData
{
public:
	AnnData(int input);
	~AnnData();

	int inputUnit;
	int classNum;
	vector<string> dataDir;
	vector<string> className;
	vector< vector<string> > dataPaths;

	vector< vector<double> > sampleInput;
	vector< vector<double> > targetLabel;

public:
	bool getDataDir(string dirStr);
	bool addData(string dirStr, string classStr);
	bool getDataSet(string dirStr);
	bool getDataPaths();
	bool getDataFromeFile();

private:

};

#endif