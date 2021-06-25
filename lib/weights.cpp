#include "data_type.hpp"
#include <vector>
template <typename T>

/*template <_1D_vector<double>,_1D_vector<double>,_2D_vector<double>,double> class nn*/
template <typename I, typename O,typename W,typename D>
class nn: public tensor<W>{
	tensor<W> wt();
	nn(){}
	conv1d(int out, int in, int kernel_dim1){
		tensor<W> tmp (out,in,kernel_dim1,1);
		wt = tmp;
		return *this;
	}
	conv2d(int out, int in, int kernel_dim1, int kernel_dim2){
		tensor<W> tmp (out,in,kernel_dim1, kernel_dim2);
		wt = tmp;
		return *this;
	}
	linear(int out, int in){
		tensor<W> tmp (out,in,1,1);
		wt = tmp;
		return *this;
	}
    vector<I>& forward(vector<I>&x){
    	/*data: channel*data_dim1*data_dim2*/
    	vector<I>res;

    	/*weights: out*in*w_dim1*w_dim2*/
    	_2D_vector<D> P(kernel_dim1*kernel_dim2*input_channel,out_dim1*out_dim2);
    	_2D_vector<D> K(output,kernel_dim1*kernel_dim2*input_channel);
    	_2D_vector<D> Z(outtput,out_dim1*out_dim2);
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
       	/*If no need to transfrom data to 2D first*/
       	column = 0;
       	for(i=0;i<wt.length();i++){
       		for(j=0;j<wt[0].length();j++){
       			for(m=0;m<wt[0][0].length();m++)
       				for(n=0;n<wt[0][0][0].length();n++)
       					K[i][column] = wt[i][j][m][n];
       					column++;
       		}
       		column = 0;
       	}
       	/*no this part*/
       	/*Z = K*P;
       	for(i=0;i<Z.length();i++){
       		for(j=0;j<out_dim1*out_dim2;j++){
       			res[i][j/out_dim1][j%out_dim1] = Z[i][j];
       		}
       	}

       	for(i=0;i<K.length();i++){
       		for(j=0;j<K[0].length();j++){
       			wt[i][j/(kernel_dim1*kernel_dim2)][j/kernel_dim1][j%kernel_dim1] = K[i][j];
       		}
       	}     	
		*/
       	/*
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
		*/
	};
	/*
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
	*/
}

