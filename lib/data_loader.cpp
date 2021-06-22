#include "data_loader.hpp"
#include <iostream>
#define datanum 500		// number of training samples
//template class data_loader<double>;
//template class data_loader<int>;
template <class T>
data_loader<T>::data_loader(){
	printf("In generic template");
}
//template class data_loader<double>::data_loader();
template <>
data_loader<double>::data_loader(){
	int i,m;
    for(m=0; m<datanum; m++){
	   for(i=0; i<InputN; i++)
		    dataset[m].input[i] = (double)rand()/32767.0;
	   for(i=0;i<OutN;i++)
		    dataset[m].teach[i] = (double)rand()/32767.0;
	}
}

