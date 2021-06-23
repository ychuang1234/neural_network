#ifndef WEIGHTS_H
#define WEIGHTS_H 1
#include "data_type.hpp"
template <typename T>
class activation_function{
public:
    T sigmoid(T x){
	   return(1.0 / (1.0 + exp(-x)));
    };
};

template <typename T,int InputN,int OutN>
class weights: public activation_function <I>{
public:
	weights() {};
	weights (data_loader<I,O>* _dataset_ptr){
        initialization();
        dataset_ptr = _dataset_ptr;
	};
	data_loader<I,O>* dataset_ptr;
	T w[OutN];		   //hidden layer
	T out[OutN];       //output layer
	T deltaw[InputN];  //derivative
	/* need to put into another class
	I delta[HN];	   //delta of hidden layer
    I errtemp,error,sumtemp;
    I max, min;
    double alpha = 0.1, beta = 0.1;
	*/
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
#endif