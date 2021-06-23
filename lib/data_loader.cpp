#include "data_loader.hpp"
#include <iostream>
//#define datanum 500		// number of training samples
//template class data_loader<double>;
//template class data_loader<int>;
template <class T>
data_loader<T>::data_loader() {}

template <class T>
data_loader<T>::data_loader(int datanum,int InputN, int OutN){
	printf("In generic data loader initialization...");
	dataset = new data[datanum];
	int m;
	for(m=0;m<datanum;m++){
		T tmp = T(InputN);
    	dataset[m].input= tmp;
		tmp = T(OutN);
    	dataset[m].teach=tmp;
	}	
}
//template class data_loader<double>::data_loader();
template <>
data_loader<double>::data_loader(int datanum,int InputN, int OutN){
	int i,m;
    for(m=0; m<datanum; m++){
	   for(i=0; i<InputN; i++)
		    dataset[m].input = (double)rand()/32767.0;
	   for(i=0;i<OutN;i++)
		    dataset[m].teach = (double)rand()/32767.0;
	}
}

