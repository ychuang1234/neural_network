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
	this->datanum = datanum;
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
	this->datanum = datanum;
	int m;
	for(m=0;m<datanum;m++){
		I input = I(Input_dim1,Input_dim2);
    	dataset[m].input= input;
		O output = O(Out_dim1,Out_dim2);
    	dataset[m].teach = output;
	}	
}
template <class I,class O>
int data_loader<I,O>::load_batch(){
    if (start_id>=batch_id) return 0;
  	D max = 0;
	D min = 0;
	int i;
	if (start_id+batch_size<dataset_ptr->datanum){
		batch_x.resize(batch_size);
		batch_y.resize(batch_size);
	}else{
		batch_x.resize(dataset_ptr->datanum-batch_size);
		batch_y.resize(dataset_ptr->datanum-batch_size);		
		}
	for(i=start_id; i<start_id+batch_size; i++){
		batch_x[i] = dataset_ptr->dataset[data_id].input[i];
		batch_y[i] = dataset_ptr->dataset[data_id].teach[i];
	}
	start_id += batch_size;
	return 1;
    /*TODO: batch normalize*/
}
//template class data_loader<double>::data_loader(int,int,int);
template <>
data_loader<double,double>::data_loader(int datanum,int Input_dim1, int Out_dim1){
	int i,m;
	this->datanum = datanum;
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


