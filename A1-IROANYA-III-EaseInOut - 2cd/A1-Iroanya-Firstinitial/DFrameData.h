#pragma once
#include <vector>
#include <iostream>
using namespace std;
class DFrameData
{
	
public:
	int number;
	vector<int> values;

	DFrameData(int number, vector<int> values) {
		this->number = number;
		this->values = values;
	}
};

