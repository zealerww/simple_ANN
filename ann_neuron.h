#ifndef ANN_NEURON_H
#define ANN_NEURON_H
#include <iostream>

class AnnNeuron
{
public:
	int inputNum;
	double *inputWeight;
	double output;
	double errSigma;

public:
	AnnNeuron(int num)
	{
		inputNum = num + 1;
		inputWeight = new double[inputNum];
		output = errSigma = 0;
	}
	~AnnNeuron()
	{
		delete []inputWeight;
	}

private:

}; //class AnnNeuron

#endif