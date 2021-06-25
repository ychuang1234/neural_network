#include <cstring>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include "data_type.hpp"
/*sigmoid*/
template <typename T>
T activation_function<T>::sigmoid(T x){
	return(1.0/ (1.0+ exp(-x)));
};
/*1D*/
template <typename T>
_1D_vector<T>::_1D_vector(){}

template <typename T>
_1D_vector<T>::_1D_vector(int len){
	data.resize(len);
}
template <typename T>
_1D_vector<T>::_1D_vector(int dim1,int dim2){}

template <typename T>
_1D_vector<T>::_1D_vector(T* start,int len){
	data.resize(len);
	std::memcpy(&(data[0]),start,len*sizeof(T));		
}
template <typename T>
int _1D_vector<T>::length(){
	return data.size();
}

template <typename T>
void _1D_vector<T>::push(T data){
	this->data.resize(length()+1);
	this->data[length()-1] = data;
}

template <typename T>
void _1D_vector<T>::push(_1D_vector<T>&data){
	int i = length();
	int j;
	this->data.resize(length()+data.length());
	for (j=0;j<data.length();j++)
		this->data[i+j] = data[j];
}

template <typename T>
void _1D_vector<T>::reshape(std::vector<_2D_vector<T>>&x,int dim1, int dim2){
	x.resize(length()/dim1/dim2);
	_2D_vector<T> tmp (dim1,dim2);
	int i;
	for(i=0;i<x.size();i++){
		x[i] = tmp;
	}
	//x[0][0].data.resize(dim2);
	for(i=0;i<this->length();){
		//printf("In 1D reshape: %d,%d,%d\n",i,i/dim1/dim2,(i%(dim1*dim2))/dim2);
		_1D_vector<T> tmp(&(this->data[i]),dim2);
		x[i/dim1/dim2][(i%(dim1*dim2))/dim2] = tmp;
		i += dim2;
	}
}

template <typename T>
T _1D_vector<T>::dot_sum( _1D_vector<T>&data){
    T res = 0;
    if (this->length()==data.length()){
    	int i;
        for (i=0;i<this->length();i++)
            res += this->data[i] * data[i];
       	return res;
    }else throw std::invalid_argument("len of two array not the same!");
}

template <typename T>
_1D_vector<T> dot(_1D_vector<T>&ldata,_1D_vector<T>&rdata){
    _1D_vector<T> res(ldata.length());
    //printf("In 1D dot\n");
    if (ldata.length()==rdata.length()){    	
    	int i;
        for (i=0;i<ldata.length();i++){
        	//printf("Here 1D:%d\n",i);
            res[i] = ldata.data[i]*rdata.data[i];
            //std::cout<<res[i]<<std::endl;
        }

       	return res;
    }else throw std::invalid_argument("len of two array not the same!");
}

template <typename T>
T& _1D_vector<T>::operator[](int i){
	//printf("In 1D []:%d,%d\n",i,length());
	if (i<length()){
		
		return data[i];
	} 
	else throw std::out_of_range("1Index out of bounds");
}

template <typename T>
std::ostream& operator<<(std::ostream& os, _1D_vector<T>& L){
	int i;
	os<<"[";
    for (i=0;i!=L.length()-1;i++)
        os<<L[i]<<",";
    os<<L[i]<<"]";
    return os;
}

template <typename T>
_1D_vector<T> operator+ (_1D_vector<T>&ldata,_1D_vector<T>&rdata){
    if (ldata.length()==rdata.length()){
    	_1D_vector<T> res(ldata.length());
    	int i;
        for (i=0;i<ldata.length();i++)
            res[i] = ldata[i]+rdata[i];
       	return res;
    }else throw std::invalid_argument("len of two array not the same!");
}

template <typename T>
_1D_vector<T> operator- (_1D_vector<T>&ldata,_1D_vector<T>&rdata){
    if (ldata.length()==rdata.length()){
    	_1D_vector<T> res(ldata.length());
    	int i;
        for (i=0;i<ldata.length();i++)
            res[i] = ldata[i]-rdata[i];
       	return res;
    }else throw std::invalid_argument("len of two array not the same!");
}

template <typename T>
_1D_vector<T> _1D_vector<T>::operator=(_1D_vector<T>data){
	//printf("In 1D assignment\n");
	this->data.resize(data.length());
	std::memcpy(&(this->data[0]),&data[0],data.length()*sizeof(T));
	return *this;
}
/*2D vector*/
template <typename T>
_2D_vector<T>::_2D_vector(){}
template <typename T>
_2D_vector<T>::_2D_vector(int dim1){}

template <typename T>
_2D_vector<T>::_2D_vector(int dim1, int dim2){
	data.resize(dim1);
	int i;
	for(i=0;i<dim1;i++){
		_1D_vector<T> tmp(dim2);
		data[i] = tmp;
	}
}

template <typename T>
_2D_vector<T>::_2D_vector(T* start,int dim1, int dim2){
	//row major
	data.resize(dim1);
	int i;
	for (i=0;i<dim1;i++){
		_1D_vector<T> tmp(start+(i*dim2*sizeof(T))/4,dim2);
		data[i] = tmp;
	}
}
template <typename T>
int _2D_vector<T>::length(){
	return data.size();
}

template <typename T>
void _2D_vector<T>::flat(_1D_vector<T>&x){
	int i,j;
	_1D_vector<T> res;
	for (i=0;i<length();i++)
		x.push(this->data[i]);
}
template <typename T>
void _2D_vector<T>::push(_1D_vector<T>&data){
	this->data.resize(length()+1);
	this->data[length()-1] = data;
}

template <typename T>
void _2D_vector<T>::push(_2D_vector<T>&data){
	int i = length();
	int j;
	this->data.resize(length()+data.length());
	for (j=0;j<data.length();j++)
		this->data[i+j] = data[j];
}

template <typename T>
T _2D_vector<T>::dot_sum(_2D_vector<T>&data){
    T res = 0;
    if (this->length()==data.length()){
    	int i;
        for (i=0;i<this->length();i++)
            res += this->data[i].dot_sum(data[i]);
       	return res;
    }else throw std::invalid_argument("len of two array not the same!");
}
template <typename T>
_2D_vector<T> dot(_2D_vector<T>&ldata,_2D_vector<T>&rdata){
    _2D_vector<T> res(ldata.length(),ldata[0].length());
    //printf("In 2D dot:%d\n",res.length(),res[0].length());
    if (ldata.length()==rdata.length()){
    	
      	int i;
        for (i=0;i<ldata.length();i++){
            //printf("Here 2D:%d\n",i);
            //std::cout<<ldata.data[i]<<std::endl;
            res[i] = dot(ldata.data[i],rdata.data[i]);
            //printf("In 2D dot done...\n");
        }
       	return res;
    }else throw std::invalid_argument("len of two array not the same!");
}
template <typename T>
_1D_vector<T>& _2D_vector<T>::operator[](int i){
	//printf("In 2D []:%d,%d\n",i,length());	
	if (i<length()){		
		return data[i];
	}
	else throw std::out_of_range("2Index out of bounds");
}

template <typename T>
std::ostream& operator<<(std::ostream& os, _2D_vector<T>& L){
	int i;
	os<<"["<<L[0]<<","<<std::endl;
    for (i=1;i!=L.length()-1;i++)
    	os<<" "<<L[i]<<","<<std::endl;
    os<<" "<<L[i]<<"]";
    return os;
}

template <typename T>
_2D_vector<T> operator+ (_2D_vector<T>&ldata,_2D_vector<T>&rdata){
    if (ldata.length()==rdata.length() && ldata[0].length()==rdata[0].length()){
    	_2D_vector<T> res(ldata.length(),ldata[0].length());
    	int i;
        for (i=0;i<ldata.length();i++)
            res[i] = ldata[i]+rdata[i];
       	return res;
    }else if(ldata.length()==rdata.length()){
		throw std::invalid_argument("len of two array in dim1 not the same!");
    }else throw std::invalid_argument("len of two array in dim2 not the same!");
}

template <typename T>
_2D_vector<T> operator- (_2D_vector<T>&ldata,_2D_vector<T>&rdata){
    if (ldata.length()==rdata.length() && ldata[0].length()==rdata[0].length()){
    	_2D_vector<T> res(ldata.length(),ldata[0].length());
    	int i;
        for (i=0;i<ldata.length();i++)
            res[i] = ldata[i]-rdata[i];
       	return res;
    }else if(ldata.length()==rdata.length()){
		throw std::invalid_argument("len of two array in dim1 not the same!");
    }else throw std::invalid_argument("len of two array in dim2 not the same!");
}

template <typename T>
_2D_vector<T> operator* (_2D_vector<T>&ldata,_2D_vector<T>&rdata){
    if (ldata[0].length()==rdata.length()){
    	_2D_vector<T> res(ldata.length(),rdata[0].length());
    	//printf("In operator *:%d,%d\n",res.length(),res[0].length());
    	int i,j,k;
        for (i=0;i<ldata.length();i++){
        	for (j=0;j<rdata[0].length();j++){
        		_1D_vector<T> tmp(rdata.length());
        		for (k=0;k<rdata.length();k++){
        			//printf("i:%d,j:%d,k:%d\n",i,j,k);
            		tmp[k] = rdata[k][j];
        		}
        		res[i][j] = ldata[i].dot_sum(tmp);
        	}
        }
            	
       	return res;
    }else throw std::invalid_argument("len of left array in dim2 and right array in dim1 not the same!");
}

template <typename T>
_2D_vector<T> _2D_vector<T>::operator=(_2D_vector<T>data){
	//printf("In 2D =%d\n",data.length());
	this->data.resize(data.length());
	int i;
	for (i=0;i<length();i++){
		this->data[i] = data[i];
	}	
	return *this;
}
/*3D vector*/
/*
template <typename T>
_3D_vector<T>::_3D_vector(){}
template <typename T>
_3D_vector<T>::_3D_vector(int dim1){}
template <typename T>
_3D_vector<T>::_3D_vector(int dim1,int dim2){}
template <typename T>
_3D_vector<T>::_3D_vector(int dim1, int dim2, int dim3){
	data.resize(dim1);
	int i;
	for(i=0;i<dim1;i++){
		_2D_vector<T> tmp(dim2,dim3);
		data[i] = tmp;
	}
}

template <typename T>
_3D_vector<T>::_3D_vector(T* start,int dim1, int dim2,int dim3){
	//row major
	data.resize(dim1);
	int i;
	for (i=0;i<dim1;i++){
		_2D_vector<T> tmp(start+(i*dim2*sizeof(T))/4,dim2,dim3);
		data[i] = tmp;
		//data[i].resize(dim2);
		//std::memcpy(&(data[i][0]),start+i*dim2*sizeof(T),dim2*sizeof(T));
	}
			
}
template <typename T>
int _3D_vector<T>::length(){
	return data.size();
}
template <typename T>
_2D_vector<T>& _3D_vector<T>::operator[](int i){
	if (i<length()) return data[i];
	else throw std::out_of_range("Index out of bounds");
}

template <typename T>
std::ostream& operator<<(std::ostream& os, _3D_vector<T>& L){
	int i;
	os<<"["<<L[0]<<","<<std::endl;
    for (i=1;i!=L.length()-1;i++)
    	os<<" "<<L[i]<<","<<std::endl;
    os<<" "<<L[i]<<"]";
    return os;
}

template <typename T>
_3D_vector<T> operator+ (_3D_vector<T>&ldata,_3D_vector<T>&rdata){
    if (ldata.length()==rdata.length() && ldata[0].length()==rdata[0].length() && ldata[0][0].length()==rdata[0][0].length()){
    	_3D_vector<T> res(ldata.length(),ldata[0].length(),ldata[0][0].length());
    	int i;
        for (i=0;i<ldata.length();i++)
            res[i] = ldata[i]+rdata[i];
       	return res;
    }else if(ldata.length()==rdata.length()){
		throw std::invalid_argument("len of two array in dim1 not the same!");
    }else if(ldata[0].length()==rdata[0].length()){
    	throw std::invalid_argument("len of two array in dim2 not the same!");
    }else throw std::invalid_argument("len of two array in dim3 not the same!");
}

template <typename T>
_3D_vector<T> operator- (_3D_vector<T>&ldata,_3D_vector<T>&rdata){
    if (ldata.length()==rdata.length() && ldata[0].length()==rdata[0].length() && ldata[0][0].length()==rdata[0][0].length()){
    	_3D_vector<T> res(ldata.length(),ldata[0].length(),ldata[0][0].length());
    	int i;
        for (i=0;i<ldata.length();i++)
            res[i] = ldata[i]-rdata[i];
       	return res;
    }else if(ldata.length()==rdata.length()){
		throw std::invalid_argument("len of two array in dim1 not the same!");
    }else if(ldata[0].length()==rdata[0].length()){
    	throw std::invalid_argument("len of two array in dim2 not the same!");
    }else throw std::invalid_argument("len of two array in dim3 not the same!");
}

template <typename T>
_3D_vector<T> _3D_vector<T>::operator=(_3D_vector<T>data){
	this->data.resize(data.length());
	int i;
	for (i=0;i<length();i++){
		this->data[i] = data[i];
	}	
	return *this;
}
*/

template <typename T,typename D>
class tensor{
public:
	//T is 2D
	std::vector<T>delta;       //delta of hidden layer:2D
	std::vector<std::vector<T>>w;		  //weights:3D (out*in*weights)
	std::vector<std::vector<T>>deltaw;    //derivative:3D (out*in*weights)
	int InputN, OutN, kernel_dim1, kernel_dim2;
	tensor(int _InputN,int _OutN,int _kernel_dim1, int _kernel_dim2):InputN(_InputN),OutN(_OutN),kernel_dim1(_kernel_dim1),kernel_dim2(_kernel_dim2){
		delta.resize(OutN);
		w.resize(OutN);
		deltaw.resize(OutN);
		int i,j;
		for(i=0;i<OutN;i++){
			w[i].resize(InputN);
			deltaw[i].resize(InputN);
			T tmp(kernel_dim1,kernel_dim2);
			for(j=0;j<InputN;j++){				
				w[i][j] = tmp;
			}
		}
		//initialize();
	};
	int dim1(){
		return w.size();
	}

	int dim2(){
		return w[0].size();
	}
    void print_w(){
    	int i,j;
    	for(i=0;i<OutN;i++){
    		std::cout<<"[";
    		std::cout<<"["<<w[i][0]<<std::endl;
    		for(j=1;j<InputN;j++){
    			//printf("Input print w:%d,%d\n",i,j);
    			std::cout<<" "<<w[i][j]<<std::endl;
    			//std::cout<<"  ";
    		}
    	}
    }
    /* according to axis 1*/
    _2D_vector<D>& _flat(){
    	_2D_vector<D> res(dim1());
    	int i,j;
    	for(i=0;i<dim1();i++){
    		for(j=0;j<dim2();j++)
    			//1D vector
    			res[i] = w[i][j].flat();
    	}
    }

    /* according to axis 1*/
    void _reshape(_2D_vector<D> data){
    	int i,j;
    	for(i=0;i<dim1();i++){
   			//vector of 2D vector
   			this->w[i] = data[i].reshape(kernel_dim1,kernel_dim2);
    	}
    }

    void initialize(){ 
		int i,j;
	    for(i=0; i<dim1(); i++)
	    	for(j=0;j<dim2();j++)
				w[i][j].initialize();
		
    }

    std::vector<T>& forward(std::vector<T>&x){
    	/*data: channel*data_dim1*data_dim2*/
    	std::vector<T>res;
    	int out_dim1,out_dim2;
		out_dim1 = x[0].length()-kernel_dim1+1;
		out_dim2 = x[0][0].length()-kernel_dim2+1;
    	/*weights: out*in*w_dim1*w_dim2*/
    	_2D_vector<D> P(kernel_dim1*kernel_dim2*InputN,out_dim1*out_dim2);
    	_2D_vector<D> K(OutN,kernel_dim1*kernel_dim2*InputN);
    	K = _flat();
    	_2D_vector<D> Z(OutN,out_dim1*out_dim2);
       	int i=0,j=0,k;
       	int row=0,column=0;
       	/*convolution: parallel?*/
       	while((i+kernel_dim1-1)<x.dim2()){
       		while((j+kernel_dim2-1)<x[0][0].length()){
       			/*for each channel*/
       			for(k=0;k<x.dim1();k++){
       				int m,n;
       				for(m=0;m<kernel_dim1;m++){
       					for(n=0;n<kernel_dim2;n++){
       						P[row][column]=x[i+m][j+n];
       						column++; 
       					}
       				}
       			}
       			i++;
       			j++;
       			column=0;
       			row++;
       		}
       	}
       	Z = K*P;
       	_reshape(Z);
      	
       	
       	for(i=0;i<Z.length();i++){
       		for(j=0;j<out_dim1*out_dim2;j++){
       			res[i][j/out_dim1][j%out_dim1] = Z[i][j];
       		}
       	}
    }
    /*
    void activate(){
    	int i,j;
    	for(i=0;i<w.size();i++){
    		for(j=0;j<w[0].length();j++){
    			activation_function<I>::sigmoid(w[i][j]);		
    		}
    	}
    }
    */
    
    
	std::vector<T>& operator[](int i){
		if (i<dim1()) return w[i];
		else throw std::out_of_range("Index out of bounds");
	}

	tensor<T,D> operator=(tensor<T,D>data){
		this->w.resize(data.dim1());
		this->deltaw.resize(data.dim1());
		this->delta.resize(data.dim1());
		int i,j;
		for (i=0;i<dim1();i++){
			this->w[i].resize(dim2());
			this->deltaw[i].resize(dim2());
			this->delta[i] = data.delta[i];
			for(j=0;j<dim2();j++){
				this->w[i][j] = data.w[i][j];
				this->deltaw[i][j] = data.deltaw[i][j];
			}
		}
		return *this;
	}
};



int main(){
	
	int a[] = {0,1,2,3,4,5};
	int b[] = {5,6,7,8,9,10};
	int r;
	_1D_vector<int> x(&a[0],6);
	_1D_vector<int> y(&b[0],6);
	_2D_vector<int> i(&a[0],3,2);
	_2D_vector<int> j(&b[0],3,2);
	_2D_vector<int> k(&a[0],2,3);
	
	std::cout<<x<<std::endl;
	std::cout<<y<<std::endl;
	std::cout<<i<<std::endl;
	std::cout<<j<<std::endl;
	std::cout<<k<<std::endl;
	_1D_vector<int>z = dot(x,y);
	int c = x.dot_sum(y);
	_2D_vector<int>l = dot(i,j);
	_2D_vector<int>m = i*k;
	_1D_vector<int> tmp;
	std::vector<_2D_vector<int>> tmp1;
	m.flat(tmp);
	tmp.reshape(tmp1,3,1);
	std::cout<<z<<std::endl;
	std::cout<<c<<std::endl;
	std::cout<<l<<std::endl;
	std::cout<<m<<std::endl;
	std::cout<<tmp<<std::endl;
	std::cout<<tmp1[0]<<std::endl;
	
	tensor<_2D_vector<int>,int>tmp3(4,2,3,3);
	std::cout<<tmp3[0][0]<<std::endl;
	tmp3.print_w();
	//tmp._flat();
}
