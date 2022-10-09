#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "KeyFrame.h"
using namespace std;

class Obj {
	int id;
	string name;
	vector<KeyFrame> keyFrames;
public:
	float posX, posY, posZ, rX, rY, rZ, sX, sY, sZ;
	float alpha = 1;
	float r = 1, g = 1, b = 1;

	Obj(int id, string name) {
		this->id = id;
		this->name = name;
	}

	void updateAtrr(float posX,float posY, float posZ, float rX, float rY, float rZ, float sX, float sY, float sZ) {
		this->posX = posX;
		this->posY = posY;
		this->posZ = posZ;
		this->rX = rX;
		this->rY = rY;
		this->rZ = rZ;
		this->sX = sX;
		this->sY = sY;
		this->sZ = sZ;
	}


	void addKeyFrame(KeyFrame keyFrame) {
		keyFrames.push_back(keyFrame);
	}
	vector<KeyFrame> getKeyFrames() {
		return keyFrames;
	}

	int getId() {
		return id;
	}

};