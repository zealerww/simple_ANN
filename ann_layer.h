#ifndef ANN_LAYER_H
#define ANN_LAYER_H

#include "ann_neuron.h"
#include <vector>
#include <iostream>
using std::vector;

/**	class of network layer
 *	Members:
 *		neurons: the AnnNeuron objects in the layer	
 */
class AnnLayer
{
public:
	int neuronNum;
	vector<AnnNeuron*> neurons; 

public:
	AnnLayer(int num, int inputNum)
	{
		neuronNum = num;

		for(int i = 0; i < neuronNum; ++i)
		{
			neurons.push_back(new AnnNeuron(inputNum));
		}
	}
	~AnnLayer()
	{
		for(int i = 0; i < neuronNum; ++i)
			delete neurons[i];
	}
	//copy construct
	//copy = operation
private:

}; //class AnnLayer

#endif