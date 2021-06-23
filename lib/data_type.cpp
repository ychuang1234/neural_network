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
    for (i=0;i!=L.length()-1;i++)
        os<<L[i]<<",";
    os<<L[i];
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
_1D_vector<T> _1D_vector<T>::operator=(_1D_vector<T>&data){
	this->data.resize(data.length());
	std::memcpy(&(this->data[0]),&data[0],data.length()*sizeof(T));
	return *this;
}
/*
int main(){
	int a[] = {0,1,2,3,4};
	int b[] = {5,6,7,8,9};
	_1D_vector<int> x(&a[0],5);
	_1D_vector<int> y(&b[0],5);
	std::cout<<x<<std::endl;
	std::cout<<y<<std::endl;
	_1D_vector<int>z = x+y;
	_1D_vector<int>l = x-y;
	std::cout<<z<<std::endl;
	std::cout<<l<<std::endl;
	
}
*/