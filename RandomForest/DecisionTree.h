#ifndef DECISIONTREE_
#define DECISIONTREE_
#include "DataDef.h"
#include <vector>
using namespace std;


void trainTree(const DataSet *dataSet,vector<Node> &dtree,const  double tolS, const int tolN,const int threadIndex);
void predictOnDataSet(const DataSet *testDataSet ,const vector<Node> &dTree,const int threadIndex);
void getTrainedNode(vector<Node> &dtree,const int threadIndex);

#endif