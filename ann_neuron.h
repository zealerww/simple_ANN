#ifndef ANN_NEURON_H
#define ANN_NEURON_H
#include <iostream>


/*	class of neuron unit
 *	Members:
 *		inputWeight: weight of input from last layer
 *		ouput: sum of weight multis input for each unit
 */
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