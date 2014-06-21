#include "LoadData.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <boost\lexical_cast.hpp>


using namespace std;

void split(string &str,const char *delim,int res[MAX_FEATURE], int &size){
	char *cstr,*p;
	cstr = new char[str.size() +1];
	strcpy(cstr,str.c_str());
	p = strtok(cstr,delim);
	size = 0;
	while(p != NULL){
		res[size ++] = atoi(p);
		p = strtok(NULL,delim);
	}
	delete cstr;
}
void vecCopy(int dst[],const int src[],int size){
	for( int i = 0;i < size; i++){
		dst[i] = src[i];
	}
}

void LoadData(const char *filePath ,DataSet *dataSet){
	ifstream ifs;
	string str;
	dataSet->dataSize = 0;
	dataSet->featureSize = 0;
	dataSet->labelCol = 1;
	cout<<"Start read file"<<endl; 
	try{
		ifs.open(filePath);
		if(!ifs){
			cout<<"Not Open file: "<<filePath<<endl;
			return ;
		}
		getline(ifs,str);
	}catch(ifstream::failure ex){
		cout<<"Cannot open file"<<*filePath<<endl;
		return ;
	}
	int ds = 0;
	int cols = 0;
	while(!ifs.eof())
	{
		try{
			getline(ifs,str);
			if(str.size() == 0){
				break;
			}
			int sample[MAX_FEATURE];
			split(str,",",sample,cols);
			vecCopy((dataSet->data)[ds++],sample,cols); 
		}catch (ifstream::failure ex){
			cout<<"Cannot read line from file"<<endl;
			return ;
		}		
	}
	dataSet->dataSize = ds;
	dataSet->featureSize = cols;
	cout<<"End Reading File"<<endl;
}