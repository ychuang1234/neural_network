/************************************************
* Backpropagation algorithm.
*
* Training a Neural Network, or an Autoencoder.
*
************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <climits>
#include "data_loader_instantiated.hpp"
#define InputN 64		// number of neurons in the input layer
#define HN 25			// number of neurons in the hidden layer
#define OutN 64			// number of neurons in the output layer
//#define datanum 500		// number of training samples

int datanum = 500;
template <typename T>
class activation_function{
public:
    T sigmoid(T x){
	   return(1.0 / (1.0 + exp(-x)));
    };
};


template <typename I,typename O>
class weights: public activation_function <I>{
public:
	weights() {};
	weights (data_loader<I,O>* _dataset_ptr){
        initialization();
        dataset_ptr = _dataset_ptr;
	};
	data_loader<I,O>* dataset_ptr;
	I x_out[InputN];		// input layer
	I hn_out[HN];			// hidden layer
	I y_out[OutN];         // output layer
	I y[OutN];				// expected output layer
	I w[InputN][HN];		// weights from input layer to hidden layer
	I v[HN][OutN];			// weights from hidden layer to output layer
	
	I deltaw[InputN][HN];  
	I deltav[HN][OutN];	
	
	I hn_delta[HN];		// delta of hidden layer
	I y_delta[OutN];		// delta of output layer
    I errtemp,error,sumtemp;
    I max, min;
	double alpha = 0.1, beta = 0.1;
	int data_id = 0;
	void initialization(){ 
		int i,j;
	    for(i=0; i<InputN; i++){
		    for(j=0; j<HN; j++){
			    w[i][j] = ((I)rand()/32767.0)*2-1;
			    deltaw[i][j] = 0;
		    }
	    }
	    for(i=0; i<HN; i++){
		   for(j=0; j<OutN; j++){
			   v[i][j] = ((I)rand()/32767.0)*2-1;
			   deltav[i][j] = 0;
		    }
	    }
    };
    void run(){
        error = 0;
        data_id = 0;
        for(data_id;data_id<datanum;data_id++){
		    feedforward();
		    backpropagation();
        }
    };
    void feedforward(){
    	int i,j;
  		max = 0.0;
		min = 0.0;
		for(i=0; i<InputN; i++){
			x_out[i] = dataset_ptr->dataset[data_id].input[i];
			if(max < x_out[i])
				max = x_out[i];
			if(min > x_out[i])
				min = x_out[i];
		}
		for(i=0; i<InputN; i++){
		    x_out[i] = (x_out[i] - min) / (max - min);
		}
    	for(i=0; i<OutN ; i++){
		    y[i] = dataset_ptr->dataset[data_id].teach[i];
		}
		for(i=0;i<HN;i++){
			sumtemp = 0;
	    	for(j=0; j<InputN; j++)
	    		sumtemp += w[j][i] * x_out[j];
	    	hn_out[i] = activation_function<I>::sigmoid(sumtemp);
	    }
   		for(i=0; i<OutN; i++){
		    sumtemp = 0;
		    for(j=0; j<HN; j++)
		    	sumtemp += v[j][i] * hn_out[j];
		    y_out[i] = activation_function<I>::sigmoid(sumtemp);
		}
	};

	void backpropagation(){
		int i,j;
		for(i=0; i<OutN; i++){
			errtemp = y[i] - y_out[i];
			y_delta[i] = -errtemp * activation_function<I>::sigmoid(y_out[i]) * activation_function<I>::sigmoid((1.0 - y_out[i]));
			error += errtemp * errtemp;
		}

		for(i=0; i<HN; i++){
			errtemp = 0.0;
			for(j=0; j<OutN; j++)
				errtemp += y_delta[j] * v[i][j];
			hn_delta[i] = errtemp * (1.0 + hn_out[i]) * (1.0 - hn_out[i]);
		}

		// Stochastic gradient descent
		for(i=0; i<OutN; i++){
			for(j=0; j<HN; j++){
				deltav[j][i] = alpha * deltav[j][i] + beta * y_delta[i] * hn_out[j];
				v[j][i] -= deltav[j][i];
			}
		}

		for(i=0; i<HN; i++){
			for(j=0; j<InputN; j++){
				deltaw[j][i] = alpha * deltaw[j][i] + beta * hn_delta[i] * x_out[j];
				w[j][i] -= deltaw[j][i];
			}
		}
		error = error / 2;
	};
};
int main(){
	char buffer[200];
	double errlimit = 0.001;

	int loop = 0;
	int times = 5000;    
	// Generate data samples
	data_loader<_1D_vector<double>,_1D_vector<double>> training_data(datanum,InputN,OutN);
	/*
	//weights initializetion
    weights<double,_1D_vector<double>> w(&training_data);
	
	// Training
	while(loop < times){		
        w.run();		
		if(w.error < errlimit) break;
		if(loop%100==0){
		   printf("The %d th training, error: %f\n", loop, w.error);
		}
		loop++;
	}
	*/
    return 0;
}

