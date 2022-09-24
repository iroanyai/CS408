#pragma once
#include "Shapes.h"
#include <vector>
#include "Camera2D.h"
#include < GL/freeglut.h>
#include <algorithm>

class Game {

	Camera2D* camera;
	bool startGame = false;
public:

	Game() {
		camera = new Camera2D();
	}

	void onKeyDown(int key) {
		if (key == ' ') {
			cout << "u\n";
		}
	}
	void onKeyUp(int key) {
		
	}

	void update() {


	}

	void draw() {
		camera->draw();
	}
};