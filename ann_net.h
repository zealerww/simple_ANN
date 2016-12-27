#ifndef ANN_NET_H
#define ANN_NET_H

#include "ann_layer.h"
#include <ctime>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using std::string;


#define BIAS 1.0

/**	class of network
 *	contains of input layer, hidden layers and output layer.
 *	use data to train the network, the weight of each neuron
 *	will be updated.use data to predict, the predicted lable
 *	will be output.
 *	Members:
 *		hiddenLayer/ouputLayer: layer contains many neurons
 *	Funcs:
 *		
 */ 

class AnnNet
{
public:
	int inputUnit;
	int outputUnit;
	int hiddenUnit;

	int hiddenLayerNum;

	int maxEpoch;	//epoch次数
	double minError;	//误差阈值
	double learningRate; //related with weight update

	int epochNum;	//当前epoch的次数
	double errSum;	//一个epoch的总误差
	double errPerSample;	//每个样本训练的误差

	//bool isStop;

	AnnLayer* hiddenLayer;
	AnnLayer* outputLayer;

	vector<double> trainErr;	//所有epoch的误差

public:
	AnnNet(int input, int output, int hidden);
	~AnnNet();
	void initNet();
	bool calculateOuput(vector<double> &input, vector<double> &output);
	double activateFunc(double input);
	bool trainEpoch(vector< vector<double> > &sampleInput, \
		vector< vector<double> > &targetLabel);
	bool train(vector< vector<double> > &sampleInput, \
		vector< vector<double> > &targetLabel);
	bool predict(vector<double> &imgVec, vector<double> &output, double &confidence, \
		int &maxValueLabel);
	void setMaxEpoch(int num);
	void setMinError(double err);
	void setLearningRate(double rate);

private:
};

#endif