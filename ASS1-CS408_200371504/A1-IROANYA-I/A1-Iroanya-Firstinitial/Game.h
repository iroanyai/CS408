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

	vector<Particle*> particles;

	Vec2 pos;
	int size;
	Color color;
	float speed;
	float angle;

	float shape;

public:

	Game() {
		camera = new Camera2D();

		pos = Vec2(1280 / 2, 720 / 2);
		size = 100;
		color = Color(0.25, 0.25, 0.25, 1);

		speed = 5;
		angle = 0;
		shape = 0.5;

	}


	void update(float deltaTime) {

		//Vec2 speed = getSpeed();
		Particle* p = new Particle(pos, Vec2(size,size), color, getSpeed(),shape);
		particles.push_back(p);

		for (int i = 0; i < particles.size();i++) {
			Particle* p = particles[i];

			p->applyForce(p->getForce());
			p->update(deltaTime);
			p->draw();

			if (p->isDead()) {
				particles.erase(particles.begin() + i);
			}
		}

		
	}

	Vec2 getSpeed() {

		int minAngle = angle - 30;
		int maxAngle = angle + 30;

		int randAngle = Utils::randRange(minAngle, maxAngle);

		double pi = 3.14159265359;
		float a = randAngle * (pi / 180);

		float x = cos(a);
		float y = sin(a);
		return Vec2(x * speed, y * speed);
	}

	//this function takes the special key input (arrow keys)
	void special(int special_key)
	{
		printf("%d \n", special_key);
		switch (special_key)
		{
		case GLUT_KEY_UP:
			speed += 5;
			break;
		case GLUT_KEY_DOWN:
			speed -= 5;
			break;
		case GLUT_KEY_LEFT:
			angle += 5;
			break;
		case GLUT_KEY_RIGHT:
			angle -= 5;
			break;
		}
	}

	//this function take char input from the user
	void onKeyDown(int key) {

		printf("%d \n", key);
		switch (key)
		{
		case 'R':
			color.r += 0.01;
			break;
		case 'r':
			color.r -= 0.01;
			break;
		case 'G':
			color.g += 0.01;
			break;
		case 'g':
			color.g -= 0.01;
			break;
		case 'B':
			color.b += 0.01;
			break;
		case 'b':
			color.b -= 0.01;
			break;
		case 'T':
			color.a += 0.01;
			break;
		case 't':
			color.a -= 0.01;
			break;
		case '+':
			size += 5;
			break;
		case '-':
			size -= 5;
			break;
		case 'a':
			pos.x -= 20;
			break;
		case 'd':
			pos.x += 20;
			break;
		case 'w':
			pos.y -= 20;
			break;
		case 's':
			pos.y += 20;
			break;
		case 'H':
			if (shape == 2) {
				shape = 3;
			}
			else {
				shape += 0.5;
			}
			break;
		case 'h':
			if (shape == 3) {
				shape = 2;
			}
			else {
				shape -= 0.5;
			}
			break;
		}

		color.r = Utils::limitNum(0.0, 1.0, color.r);
		color.g = Utils::limitNum(0.0, 1.0, color.g);
		color.b = Utils::limitNum(0.0, 1.0, color.b);
		color.a = Utils::limitNum(0.0, 1.0, color.a);

		size = Utils::limitNum(1,200,size);
		pos.x = Utils::limitNum(1280.0f / 4, 1280 - 1280.0f/4, pos.x);
		pos.y = Utils::limitNum(720.0f / 4, 720.0f - 720.0f / 4, pos.y);

		speed = Utils::limitNum(0.0, 10.0, speed);
		shape = Utils::limitNum(0.5, 3.0, shape);


	}
	void onKeyUp(int key) {
		
	}

	void draw() {
		
		string red = "Red (R (INCREASE), r (DECREASE)) : " + std::to_string(color.r);
		string green = "Green (G (INCREASE), g (DECREASE)): " + std::to_string(color.g);
		string blue = "Blue (B (INCREASE), b (DECREASE)): " + std::to_string(color.b);
		string alpha = "Transparency (T (INCREASE), t (DECREASE)): " + std::to_string(color.a);
		string sizeStr = "Size (+ (INCREASE),  - (DECREASE)): " + std::to_string(size);
		string x = "X pos (d (INCREASE), a (DECREASE)): " + std::to_string(pos.x);
		string y = "Y pos (w (INCREASE), s (DECREASE)): " + std::to_string(pos.x);
		string speedStr = "Speed (UP arrow (INCREASE), DOWN arrow(DECREASE)): " + std::to_string(speed);
		string angleStr = "Movement Direction (LEFT arrow (INCREASE), RIGHT arrow(DECREASE)): " + std::to_string(angle);
		string shapeStr = "Shape (H (INCREASE), h (DECREASE)): " + std::to_string(shape);

		
		Shapes::drawText( 5, 30, red.c_str() , Color(1, 0.3, 0.3f));
		Shapes::drawText( 5, 50, green.c_str(), Color(0,3, 1, 0.3f));
		Shapes::drawText(5, 70, blue.c_str(), Color(0.3, 0.3, 1));
		Shapes::drawText(5, 90, alpha.c_str());
		Shapes::drawText(5, 110, sizeStr.c_str());
		Shapes::drawText(5, 130, x.c_str());
		Shapes::drawText(5, 150, y.c_str());
		Shapes::drawText(5, 170, speedStr.c_str());
		Shapes::drawText(5, 190, angleStr.c_str());
		Shapes::drawText(5, 210, shapeStr.c_str());
	}
};