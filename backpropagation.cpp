/************************************************
* Backpropagation algorithm.
*
* Training a Neural Network, or an Autoencoder.
*
************************************************/

#include <stdio.h>
#include <afx.h>
#include <math.h>
#include <stdlib.h>

#define InputN 64		// number of neurons in the input layer
#define HN 25			// number of neurons in the hidden layer
#define OutN 64			// number of neurons in the output layer
#define datanum 500		// number of training samples
template <typename T>
class activation_function{
public:
    T sigmoid(T x){
	   return(1.0 / (1.0 + exp(-x)));
    };
}

template <typename T>
class weights: public activation_function <T>{
public:
	weights();// constructor with parameter?
	T x_out[InputN];		// input layer
	T hn_out[HN];			// hidden layer
	T y_out[OutN];         // output layer
	T y[OutN];				// expected output layer
	T w[InputN][HN];		// weights from input layer to hidden layer
	T v[HN][OutN];			// weights from hidden layer to output layer
	
	T deltaw[InputN][HN];  
	T deltav[HN][OutN];	
	
	T hn_delta[HN];		// delta of hidden layer
	T y_delta[OutN];		// delta of output layer

	// Initializition
	void initialization(){ 
	    for(i=0; i<InputN; i++){
		    for(j=0; j<HN; j++){
			    w[i][j] = ((T)rand()/32767.0)*2-1;
			    deltaw[i][j] = 0;
		    }
	    }
	    for(i=0; i<HN; i++){
		   for(j=0; j<OutN; j++){
			   v[i][j] = ((double)rand()/32767.0)*2-1;
			   deltav[i][j] = 0;
		    }
	    }
    };

    void feedforward(){
    	for(m=0; m<datanum ; m++){
			max = 0.0;
			min = 0.0;
			for(i=0; i<InputN; i++){
				x_out[i] = data[m].input[i];
				if(max < x_out[i])
					max = x_out[i];
				if(min > x_out[i])
					min = x_out[i];
			}
		for(i=0; i<InputN; i++){
			x_out[i] = (x_out[i] - min) / (max - min);
		}

		for(i=0; i<OutN ; i++){
			y[i] = data[m].teach[i];
		}

		for(i=0; i<HN; i++){
			sumtemp = 0.0;
			for(j=0; j<InputN; j++)
				sumtemp += w[j][i] * x_out[j];
			hn_out[i] = sigmoid(sumtemp);		// sigmoid serves as the activation function
		}

		for(i=0; i<OutN; i++){
			sumtemp = 0.0;
			for(j=0; j<HN; j++)
				sumtemp += v[j][i] * hn_out[j];
		    y_out[i] = sigmoid(sumtemp);
		}
	};
	void backpropagation(){
		for(i=0; i<OutN; i++){
			errtemp = y[i] - y_out[i];
			y_delta[i] = -errtemp * sigmoid(y_out[i]) * (1.0 - sigmoid(y_out[i]));
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
	};

}
int main(){
	double sigmoid(double);
	CString result = "";
	char buffer[200];
    weights<double> w;

	double error;
	double errlimit = 0.001;
	double alpha = 0.1, beta = 0.1;
	int loop = 0;
	int times = 50000;
	int i, j, m;
	double max, min;
	double sumtemp;
	double errtemp;
	
	// training set
	struct{
		double input[InputN];
		double teach[OutN];
	}data[datanum];
	
	// Generate data samples
	// You can use your own data!!!
	for(m=0; m<datanum; m++){
		for(i=0; i<InputN; i++)
			data[m].input[i] = (double)rand()/32767.0;
		for(i=0;i<OutN;i++)
			data[m].teach[i] = (double)rand()/32767.0;
	}

	// Training
	while(loop < times){
		loop++;
		error = 0.0;
        w.feedforward();
        w.backpropagation();
		// Global error 
		error = error / 2;
		if(loop%1000==0){
			result = "Global Error = ";
			sprintf(buffer, "%f", error);
			result += buffer;
			result += "\r\n";
		}
		if(error < errlimit)
			break;

		printf("The %d th training, error: %f\n", loop, error);
	}

}

