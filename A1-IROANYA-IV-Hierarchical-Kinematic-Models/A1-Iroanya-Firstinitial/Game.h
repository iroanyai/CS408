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
#include "Sphere.h"
#include "AnimationTest.h"
#include "Person.h"

#define PI 3.14159265


class Game {

	Camera2D* camera;
	bool startGame = false;

	//AnimationTest aniTest;

	//vector<Obj*> objs;

	float countTime = 0;
	float keyTime = 0;

	vector<Vec3> points;


	double sphereX = 0;
	double sphereY = 0;

	float time = 0;

	Person person;

public:


	Game() {
		camera = new Camera2D();

	}

	void update(float deltaTime) {
		if (Utils::mode == Utils::None) {
			return;
		}

		time += deltaTime;
	}
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {

	}

	void draw() {

		person.display_axes();
		person.display_person();

		// for draw curve
		glLineWidth(1);
		Shapes::drawSpere(10, 10, 30, 3.0f);
	}




};