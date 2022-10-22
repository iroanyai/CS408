#pragma once
#include "Shapes.h"
#include <vector>
#include "Camera2D.h"
#include < GL/freeglut.h>
#include <algorithm>
#include "Utils.h"
#include "Particle.h"
#include <iostream>
#include <string>
#include "AnimationTest.h"
#include "DoublyLinkedList.h"

#define PI 3.14159265
class Game {

	float time;

public:


	Game() {

		test1();
	}

	void test1() {
		dLinkedList* frames = new dLinkedList();
		frames->headInsert(new DFrameData(1,  {10,10,10} ));
		frames->headInsert(new DFrameData(2,  {20,20,30} ));
		frames->headInsert(new DFrameData(3,  {30,80,50} ));
		frames->headInsert(new DFrameData(4,  {40,50,60} ));
		frames->headInsert(new DFrameData(5,  {50,60,70} ));
		
		int f = 0;
		for (node* frameNode = frames->head; frameNode->next != nullptr; frameNode = frameNode->next) {
			for (int i = 0; i < frameNode->data->values.size();i++) {

				float u = (f - frameNode->data->values[i]) / (frameNode->next->data->values[i] - frameNode->data->values[i]);
				float a = (1 - u) * (frameNode->data->values[i]) + u * (frameNode->next->data->values[i]);

				cout << u << " : " << a << "\n";

			}
			f++;
		}

	}

	void update(float deltaTime) {
		time += deltaTime;

		
	}
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {
		
	}

	void draw() {

	}
};