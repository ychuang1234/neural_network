#include "data_type.hpp"
#include <vector>
template <typename T>
class activation_function{
public:
    T sigmoid(T x){
	   return(1.0 / (1.0 + exp(-x)));
    };
};
/*template <_1D_vector<double>,_1D_vector<double>,_2D_vector<double>,double> class nn*/
template <typename I, typename O,typename W,typename D>
class nn: public tensor<W>{
	nn(){}
	nn.conv1d(int out, int in, int kernel_dim1){
		w = tensor<W>::weights(out,in,kernel_dim1,1);
	}
	nn.conv2d(int out, int in, int kernel_dim1, int kernel_dim2){
		w = tensor<W>::weights(out,in,kernel_dim1, kernel_dim2);
	}
	nn.linear(int out, int in){
		w = tensor<W>::weights(out,in,1,1);
	}
    void forward(vector<I>&x){
    	/*data: channel*data_dim1*data_dim2*/
    	vector<I>res;
    	/*weights: out*in*w_dim1*w_dim2*/
    	_2D_vector<D> P(kernel_dim1*kernel_dim2*input_channel,out_dim1*out_dim2);
    	_2D_vector<D> K(output,kernel_dim1*kernel_dim2*input_channel);
       	int i=0,j=0,k;
       	int row=0,column=0;
       	/*convolution: parallel?*/
       	while((i+kernel_dim1-1)<x[0].length()){
       		while((j+kernel_dim2-1)<x[0][0].length()){
       			/*for each channel*/
       			for(k=0;k<x.length();k++){
       				int m,n;
       				for(m=0;m<kernel_dim1;m++)
       					for(n=0;n<kernel_dim2;n++)
       						P[row][column]=x[i+m][j+n]
       						column++; 
       			}
       			i++;
       			j++;
       			column=0;
       			row++;
       		}
       	}
       	

        int i,dim;
        for(i=0;i<output;i++){
        	for (j=0;j<input;j++){
        		K[i].assign(w[i][j],kernel_dim1*kernel_dim2); 
        	}
        }
    	int i,j;
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
}
template <typename T>
class tensor: public activation_function <T>{
public:
	//T is 2D
	vector<T>delta;       //delta of hidden layer:2D
	vector<*T>w;		  //weights:3D (out*in*weights)
	vector<*T>deltaw;    //derivative:3D (out*in*weights)
	weights(int InputN,int OutN,int kernel_dim1, int kernel_dim2) {
		delta.resize(OutN);
		w.resize(OutN);
		deltaw.resize(OutN);
		int i;
		for(i=0;i<OutN;i++){
			w = new T(kernel_dim1,kernel_dim2)[InputN];
			deltaw = new T(kernel_dim1,kernel_dim2)[OutN];
		}
		initialize();
	};

	void initialize(){ 
		int i,j;
	    for(i=0; i<OutN; i++)
	    	for(j=0;j<InputN;j++)
				w[i][j].initialize();
		
    }
	/* need to put into another class
	
    T errtemp,error,sumtemp;
    T max, min;
    double alpha = 0.1, beta = 0.1;
	int data_id,datanum;
	*/

    /*need to put into another class
    void run(){
        error = 0;
        data_id = 0;
        for(data_id;data_id<datanum;data_id++){
		    feedforward();
		    backpropagation();
        }
    };
    */

};
