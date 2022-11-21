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

public:

	Game() {
		camera = new Camera2D();
		srand(time(nullptr));

		// creative
		gass.push_back(Gas(20,20,100,100));
		gass.push_back(Gas(500, 20,200,200));
		gass.push_back(Gas(500, 500,100,100));

		gass.push_back(Gas(100, 100, 500, 500));
		gass.push_back(Gas(50, 500, 200, 200));
		gass.push_back(Gas(50, 100, 200, 300));
	}


	void update(float deltaTime) {

		// creative
		for (int i = 0; i < gass.size(); i++) {
			gass[i].update();
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