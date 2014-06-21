#include <vector>
#include <boost\thread.hpp>

#include <iostream>
#include <stdlib.h>
#include "LoadData.h"
#include "DataDef.h"
#include <string>
#include <algorithm>
#include "DecisionTree.h"
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;
const int start = 0;
const int tree_per_thread = 1;
void run(const DataSet *dataSet,const DataSet *testSet, const int threadCount){
	int treeIndex = threadCount * tree_per_thread;
	for(int i = 0;i  < tree_per_thread ;i ++){
		vector<Node> dtree;
		double tolS = 0.0001;
		int tolN = 1;
		cout<<"Current	tree :"<<treeIndex<<endl;
		trainTree(dataSet,dtree,tolS,tolN,treeIndex);
		
		//getTrainedNode(dtree,threadCount);

		if (dataSet->featureSize - 1 != testSet->featureSize)
		{
			cout<<"Size not match "<<endl;
		}
		else{
		//string outputPath = "output.csv";
			predictOnDataSet(testSet,dtree,treeIndex);	
		}
		treeIndex += 1;
	}
}

void writeFinalOutputToDisk(const string outputFile,const int predictLabels[],const int predictSize){
	int numOfTestCases = predictSize;
	ofstream ofs;
	try{

		ofs.open(outputFile.c_str(),std::ofstream::out | std::ofstream::trunc);
		ofs<<"Id,label"<<endl;
		for(int i = 0;i < numOfTestCases;i ++){

			int castId = i + 1;
			int predictLabel = predictLabels[i];
			ofs<<castId<<","<<predictLabel<<endl;
		}
		ofs.close();
	}catch (ofstream::failure ex){
		cout<<"Cannot writ to predict file"<<endl;
	}
}
int sampleLabelVotes[MAX_DATA_SIZE][NUM_CLASS] = {0};

void _voteForOutput(const string outputFile){
	
	int predictDataSize = 0;

	for(int i = start;i < start + NUM_THREAD;i++){
		int treeIndex = i * tree_per_thread;
		cout<<"Combining: "<<treeIndex<<endl;
		for(int j = 0; j < tree_per_thread ;j ++){
			DataSet *outputSet = new DataSet();
			stringstream ss;
			ss << "data\\output"<< treeIndex << ".csv";
		
			LoadData(ss.str().c_str(),outputSet);

			for(int j = 0;j < outputSet->dataSize ;j++){
				int predictLabel = (outputSet->data)[j][outputSet->labelCol];

				sampleLabelVotes[j][predictLabel] += 1;
			}
			predictDataSize = outputSet->dataSize;
			delete outputSet;
			treeIndex += 1;
		}
	}

	int votedOutput[MAX_DATA_SIZE] = {0};
	for(int i = 0; i < predictDataSize;i++){
		int maxCount = -1;
		int maxLabel = 0;
		for(int  j = 0;j <NUM_CLASS ;j ++){
			if( sampleLabelVotes[i][j] >= maxCount){
				maxLabel = j;
				maxCount = sampleLabelVotes[i][j];
				
			}
		}
		votedOutput[i] = maxLabel;
	}
	writeFinalOutputToDisk(outputFile,votedOutput,predictDataSize);
	
}

int main(int argc, char *arg[])
{
	time_t start_time = time(NULL);
	DataSet *dataSet = new DataSet();
	string trainPath = "data\\train_s_o.csv";

	LoadData(trainPath.c_str(),dataSet);
	
	time_t readTrainFileTime = time(NULL);
	cout<<"read train file time: "<<readTrainFileTime - start_time<<" s"<<endl;
	
	DataSet *testSet = new DataSet();
	string testPath = "data\\test_s_o.csv";
	LoadData(testPath.c_str(),testSet);
	time_t readTestFileTime = time(NULL);
	cout<<"Read test file time: "<<readTestFileTime-readTrainFileTime <<"s"<<endl;

	//start train tree
	
	boost::thread_group tgr;
	//vector<vector<Node>> treeVec = vector<vector<Node>>(NUM_THREAD);
	
	for(int i = start;i < start + NUM_THREAD ;i ++){

	//	getTrainedNode(treeVec[i],i);
		tgr.create_thread(boost::bind(&run,dataSet,testSet,i));
	}
	tgr.join_all();
	
	
	time_t trainTime = time(NULL);
	cout<<"Train Time: "<<float((trainTime - readTestFileTime))/60.0 <<"min"<<endl;
	
	//long testTime = time(NULL);
	//cout << "Test time: "<<(testTime - readTestFileTime)<<"s"<<endl;
	delete dataSet;
	delete testSet;

	// combine all the output
	
	_voteForOutput("output.csv");

	time_t combineTime = time(NULL);
	cout<<"Combiine time: "<<combineTime - trainTime <<"s"<<endl;

	system("PAUSE");
	return 0;
}
