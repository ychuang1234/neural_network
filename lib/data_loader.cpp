#include "data_loader.hpp"
#include <iostream>
//#define datanum 500		// number of training samples
//template class data_loader<double>;
//template class data_loader<int>;
template <class I,class O>
data_loader<I,O>::data_loader() {}

template <class I,class O>
data_loader<I,O>::data_loader(int datanum,int Input_dim1, int Out_dim1){
	printf("In generic data loader initialization...");
	dataset = new data[datanum];
	int m;
	for(m=0;m<datanum;m++){
		I input = I(Input_dim1);
    	dataset[m].input= input;
		O output = O(Out_dim1);
    	dataset[m].teach = output;
	}	
}

template <class I,class O>
data_loader<I,O>::data_loader(int datanum,int Input_dim1,int Input_dim2, int Out_dim1,int Out_dim2){
	printf("In generic data loader initialization...");
	dataset = new data[datanum];
	int m;
	for(m=0;m<datanum;m++){
		I input = I(Input_dim1,Input_dim2);
    	dataset[m].input= input;
		O output = O(Out_dim1,Out_dim2);
    	dataset[m].teach = output;
	}	
}

//template class data_loader<double>::data_loader(int,int,int);
template <>
data_loader<double,double>::data_loader(int datanum,int Input_dim1, int Out_dim1){
	int i,m;
    for(m=0; m<datanum; m++){
	   for(i=0; i<Input_dim1; i++)
		    dataset[m].input = (double)rand()/32767.0;
	   for(i=0;i<Out_dim1;i++)
		    dataset[m].teach = (double)rand()/32767.0;
	}
}
template <>
data_loader<double,double>::data_loader(int datanum,int Input_dim1,int Input_dim2, int Out_dim1, int Out_dim2){
}


