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
		//Shapes::drawRect(Rect(20, 20, 300, 300), Color(0.4, 0.25, 0.25,1));

		Shapes::drawShape1(Rect(500,23,50, 50), Color(1,1,1));
		Shapes::drawShape2(Rect(100, 23, 50, 50), Color(1, 0.5, 1));
		Shapes::drawShape3(Rect(100, 323, 50, 50), Color(1, 0.5, 1));
		Shapes::drawShape4(Rect(200, 323, 50, 50), Color(1, 0.5, 1));
		Shapes::drawShape5(Rect(400, 323, 50, 50), Color(1, 0.5, 1));

		Shapes::drawText( 5, 30, "'G' - change green");
	}
};