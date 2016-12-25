#include "ann_data.h"
#include <opencv2/opencv.hpp>
using namespace cv;

AnnData::AnnData(int input)
{
	inputUnit = input;
	classNum = 0;
}

AnnData::~AnnData()
{}

bool AnnData::addData(string dirStr, string classStr)
{
	dataDir.push_back(dirStr);
	className.push_back(classStr);
	classNum++;
	return true;
}

bool AnnData::getDataDir(string dirStr)
{
	DIR *dir = opendir(dirStr.c_str());
	struct dirent *ent;

	while((ent = readdir(dir)) != NULL)
	{
		if(ent->d_type & DT_DIR)
		{
			if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
			{
				dataDir.push_back(dirStr + "/" + ent->d_name);
				className.push_back(ent->d_name);
				classNum++;
				//test use
				cout << dirStr << "/" << ent->d_name << endl;
			}
		}

	}
	closedir(dir);

	return true;
}

bool AnnData::getDataSet(string dirStr)
{
	getDataDir(dirStr);
	getDataPaths();
	getDataFromeFile();
	return true;
}

bool AnnData::getDataPaths()
{	
	for(int i = 0; i < classNum; ++i)
	{
		vector<string> vec;

		DIR *dir = opendir(dataDir[i].c_str());
		struct dirent *ent;

		while((ent = readdir(dir)) != NULL)
		{
			if(ent->d_type & DT_REG)
			{
				//just for bmp file
				if(string(ent->d_name).find(".bmp") == string::npos)
					continue;
				vec.push_back(ent->d_name);
			}

		}
		closedir(dir);
		dataPaths.push_back(vec);
	}

	return true;
}

bool AnnData::getDataFromeFile()
{
	sampleInput.clear();
	targetLabel.clear();

	vector<double> vecInput(inputUnit, 0);

	for(int i = 0; i < classNum; ++i)
	{
		//correct label 0.9, wrong 0.1
		vector<double> label(classNum, 0.1);
		label[i] = 0.9;

		string str;
		cv::Mat img;
		for(int j = 0; j < dataPaths[i].size(); ++j)
		{
			str = dataDir[i] + "/" + dataPaths[i][j];
			img = imread(str, 0);
			if(!img.data)
			{
				cout << "error in reading " << str << endl;
				continue;
			}

			cv::resize(img, img, cv::Size(16, 32));
			int n = 0;
			for(int r = 0; r < img.rows; ++r)
			{
				uchar* data = img.ptr<uchar>(r);
				for(int c = 0; c < img.cols; ++c)
				{
					vecInput[n] = data[c] / 255.0;
					n++;
				}
			}

			targetLabel.push_back(label);
			sampleInput.push_back(vecInput);
		}
	}

	return true;
}
