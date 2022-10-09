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
class Game {

	Camera2D* camera;
	bool startGame = false;

	AnimationTest aniTest;

	vector<Obj*> objs;

	float countTime = 0;
	float keyTime = 0;
public:

	Game() {
		camera = new Camera2D();

		aniTest.test();

		objs = aniTest.getObjs();
	}


	void update(float deltaTime) {

		countTime += deltaTime;
		if (countTime >= 0.01) {
			countTime = 0;
			keyTime += 1;
			
		}
		for (int i = 0; i < objs.size(); i++) {
			
			Obj* obj = aniTest.getObjAtTime(keyTime, i);

			Color color(1, 1, 0);
			/*if (i == 0) {
				color = Color(0.5, 0.8, 0.2);
			}
			if (i == 1) {
				color = Color(1, 0.2, 0.2);
			}
			if (i == 2) {
				color = Color(0, 0.2, 1);
			}
			if (i == 5) {
				color = Color(0.502, 0.110, 0.580);
			}*/

			color.r = obj->r;
			color.g = obj->g;
			color.b = obj->b;
			color.a = obj->alpha;




			Shapes::drawRect(Rect(0, 0, 50, 50),
				obj->posX, obj->posY, obj->posZ,
				obj->rX, obj->rY, obj->rZ,
				obj->sX, obj->sY, obj->sZ, color);
		}

		if (keyTime >= 200) {
			keyTime = 0;
		}

	}
	
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {
		
	}

	void draw() {
		
		string red = "Hello world!";
		
		//Shapes::drawText( 10, 10, red.c_str() , Color(1, 0.3, 0.3f));
	}
};