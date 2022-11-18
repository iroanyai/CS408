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
#include "Gas.h"
class Game {

	Camera2D* camera;
	bool startGame = false;

	vector<Gas> gass;
	int s = 3;

public:

	Game() {
		camera = new Camera2D();
		srand(time(nullptr));

		for (int i = 0; i < s; i++) {
			gass.push_back(Gas());
		}

	}


	void update(float deltaTime) {

		for (int i = 0; i < s; i++) {
			gass[i].display(deltaTime);
		}
	}
	
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {
		
	}

	void draw() {
		
		//string red = "Hello world!";
		//Shapes::drawText( 10, 10, red.c_str() , Color(1, 0.3, 0.3f));
	}
};