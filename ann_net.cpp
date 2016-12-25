#include "ann_net.h"

using namespace std;

double getRand()
{
	double num1 = rand()/(RAND_MAX+1.0);
	double num2 = rand()/(RAND_MAX+1.0);
	return 0.1*(num1-num2);
}

AnnNet::AnnNet(int input, int output, int hidden)
{
	inputUnit = input;
	outputUnit = output;
	hiddenUnit = hidden;

	hiddenLayer = new AnnLayer(hiddenUnit, inputUnit);
	outputLayer = new AnnLayer(outputUnit, hiddenUnit);
	
	hiddenLayerNum = 1;
	errSum = 0.0;
	errPerSample = 0.0;
	epochNum = 0;
}

void AnnNet::initNet()
{
	srand((unsigned)time(NULL));

	//init hidden layer
	for(int i = 0; i < hiddenLayer->neuronNum; ++i)
	{
		for(int j = 0; j < hiddenLayer->neurons[i]->inputNum; ++j)
		{
			hiddenLayer->neurons[i]->inputWeight[j] = getRand();
		}
	}

	//init output layer
	for(int i = 0; i < outputLayer->neuronNum; ++i)
	{
		for(int j = 0; j < outputLayer->neurons[i]->inputNum; ++j)
		{
			outputLayer->neurons[i]->inputWeight[j] = getRand();
		}
	}
}

void AnnNet::setMaxEpoch(int num)
{
	maxEpoch = num;
}

void AnnNet::setMinError(double err)
{
	minError = err;
}

void AnnNet::setLearningRate(double rate)
{
	learningRate = rate;
}


//also called forward propogation
bool AnnNet::calculateOuput(vector<double> &input, vector<double> &output)
{
	if(input.size() != inputUnit)
		return false;

	double neuronOutput;

	//calculate the hidden layer output
	for(int i = 0; i < hiddenLayer->neuronNum; ++i)
	{
		neuronOutput = 0.0;
		AnnNeuron* neuron = hiddenLayer->neurons[i];
		for(int j = 0; j < neuron->inputNum-1; ++j)
		{
			neuronOutput += neuron->inputWeight[j]*input[j];
		}
		neuronOutput += neuron->inputWeight[neuron->inputNum-1]*BIAS;
		neuron->output = activateFunc(neuronOutput);
	}

	output.reserve(outputUnit);
	//calculate the output layer output
	for(int i = 0; i < outputLayer->neuronNum; ++i)
	{
		neuronOutput = 0.0;
		AnnNeuron* neuron = outputLayer->neurons[i];
		for(int j = 0; j < neuron->inputNum-1; ++j)
		{
			neuronOutput += neuron->inputWeight[j] * hiddenLayer->neurons[j]->output;
		}
		neuronOutput += neuron->inputWeight[neuron->inputNum-1]*BIAS;
		neuron->output = activateFunc(neuronOutput);
		output.push_back(neuron->output);
	}

	return true;
}

double AnnNet::activateFunc(double input)
{
	//sigmoid func
	double response = 1.0;
	return (1.0 / (1.0 + exp(-input / response)));
}

//also called back propogation
bool AnnNet::trainEpoch(vector< vector<double> > &sampleInput, \
		vector< vector<double> > &targetLabel)
{
	errSum = 0.0;

	int i, j, k;
	double err;
	double weightUpdate;

	for(i = 0; i < sampleInput.size(); ++i)
	{
		vector<double> outputLabel;
		outputLabel.reserve(outputUnit);

		//calcalute output label
		if(!calculateOuput(sampleInput[i], outputLabel))
			return false;

		//update the weight of output layer
		for(j = 0; j < outputLayer->neuronNum; ++j)
		{
			//calculate the err of output
			errSum += (targetLabel[i][j] - outputLabel[j]) * (targetLabel[i][j] \
				 - outputLabel[j]);

			AnnNeuron *neuron = outputLayer->neurons[j];
			err = (targetLabel[i][j] - outputLabel[j]) * outputLabel[j] \
				* (1.0 - outputLabel[j]);
			neuron->errSigma = err;

			//update last layer input weight
			for( k = 0; k < neuron->inputNum-1; ++k)
			{
				weightUpdate = err * learningRate * hiddenLayer->neurons[k]->output;
				neuron->inputWeight[k] += weightUpdate;
			}
			//update bias weight
			weightUpdate = err * learningRate * BIAS;
			neuron->inputWeight[k] += weightUpdate;
		}

		//update the weight of hidden layer
		for(j = 0; j < hiddenLayer->neuronNum; ++j)
		{

			AnnNeuron *neuron = hiddenLayer->neurons[j];
			err = 0.0;
			for(k = 0; k < outputLayer->neuronNum; ++k)
			{
				err += outputLayer->neurons[k]->errSigma * \
					outputLayer->neurons[k]->inputWeight[j];
			}
			err *= neuron->output * (1.0 - neuron->output);

			//update last layer input weight
			for(k = 0; k < neuron->inputNum-1; ++k)
			{
				weightUpdate = err * learningRate * sampleInput[i][k];
				neuron->inputWeight[k] += weightUpdate;
			}
			//update bias weight
			weightUpdate = err * learningRate * BIAS;
			neuron->inputWeight[k] += weightUpdate;


		}

	}

	epochNum++;
	return true;
}

bool AnnNet::train(vector< vector<double> > &sampleInput, \
		vector< vector<double> > &targetLabel)
{
	while(epochNum < maxEpoch)
	{
		if(!trainEpoch(sampleInput, targetLabel))
		{
			std::cout << "error in " << epochNum << " times!" << std::endl;
			return false;
		}

		errPerSample = errSum / (outputUnit * sampleInput.size());
		std::cout << "epoch: " << epochNum << ", error per sample:" << \
			errPerSample << std::endl;
		trainErr.push_back(errPerSample);

		if(errPerSample < minError)
			break;
	}
	//test use
	std::cout << "train finish!" << std::endl;
	return true;
}



bool AnnNet::predict(vector<double> &imgVec, vector<double> &output, double &confidence, \
		int &maxValueLabel)
{
	if(!calculateOuput(imgVec, output))
		return 0;

	//get the max/second value and max's label
	double max1 = 0, max2 = 0;
	for(int i = 0; i < output.size(); ++i)
	{
		if(output[i] > max1)
		{
			max2 = max1;
			max1 = output[i];
			maxValueLabel = i;
		}
	}

	confidence = max1 - max2;
	return true;
}

AnnNet::~AnnNet()
{
	delete hiddenLayer;
	delete outputLayer;
}

