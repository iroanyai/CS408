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
class Game {

	Camera2D* camera;
	bool startGame = false;


public:

	Game() {
		camera = new Camera2D();

	}


	void update(float deltaTime) {

	}
	
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {
		
	}

	void draw() {
		
		string red = "Hello world!";
		Shapes::drawText( 10, 10, red.c_str() , Color(1, 0.3, 0.3f));
	}
};