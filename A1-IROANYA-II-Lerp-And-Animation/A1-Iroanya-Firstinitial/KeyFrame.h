#pragma once
#pragma once
#include <iostream>
#include <string>
using namespace std;

class KeyFrame {
public:
	KeyFrame(int time, float positionX, float positionY, float positionZ,
		float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ) {
		this->time = time;
		this->positionX = positionX;
		this->positionY = positionY;
		this->positionZ = positionZ;

		this->rotationX = rotationX;
		this->rotationY = rotationY;
		this->rotationZ = rotationZ;

		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->scaleZ = scaleZ;
	}

	int time;
	float positionX, positionY, positionZ;
	float rotationX, rotationY, rotationZ;
	float scaleX, scaleY, scaleZ;
	float alpha = 1; //creative
	float r = 1, g = 1, b = 1; //creative

};