#include <cstring>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include "data_type.hpp"
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
T& _1D_vector<T>::operator[](int i){
	if (i<length()) return data[i];
	else throw std::out_of_range("Index out of bounds");
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
		//data[i].resize(dim2);
		//std::memcpy(&(data[i][0]),start+i*dim2*sizeof(T),dim2*sizeof(T));
	}
			
}
template <typename T>
int _2D_vector<T>::length(){
	return data.size();
}
template <typename T>
_1D_vector<T>& _2D_vector<T>::operator[](int i){
	if (i<length()) return data[i];
	else throw std::out_of_range("Index out of bounds");
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
_2D_vector<T> _2D_vector<T>::operator=(_2D_vector<T>data){
	this->data.resize(data.length());
	int i;
	for (i=0;i<length();i++){
		this->data[i] = data[i];
	}	
	return *this;
}
/*3D vector*/
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
_2D_vector<T>::_2D_vector(T* start,int dim1, int dim2,int dim3){
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
/*
int main(){
	int a[] = {0,1,2,3,4,5};
	int b[] = {5,6,7,8,9,10};
	int r;
	for (r=0;r<6;r++) printf("%p ",&a[r]);
	printf("\n");
	for (r=0;r<6;r++) printf("%p ",&b[r]);
	printf("\n");
	_1D_vector<int> x(&a[0],6);
	_1D_vector<int> y(&b[0],6);
	_2D_vector<int> i(&a[0],3,2);
	_2D_vector<int> j(&b[0],3,2);
	
	std::cout<<x<<std::endl;
	std::cout<<y<<std::endl;
	std::cout<<i<<std::endl;
	std::cout<<j<<std::endl;
	
	_1D_vector<int>z = x+y;
	_1D_vector<int>l = x-y;
	_2D_vector<int>k = i+j;
	_2D_vector<int>m = i-j;
	std::cout<<z<<std::endl;
	std::cout<<l<<std::endl;
	std::cout<<k<<std::endl;
	std::cout<<m<<std::endl;
}
*/