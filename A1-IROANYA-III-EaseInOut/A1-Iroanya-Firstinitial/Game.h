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
#include "BSpline.h"
class Game {

	Camera2D* camera;
	bool startGame = false;

	//AnimationTest aniTest;

	//vector<Obj*> objs;

	float countTime = 0;
	float keyTime = 0;

	vector<Vec3> points;
	Curve* curve = new BSpline();


	double sphereX = 0;
	double sphereY = 0;

	float tesetTime = 0;
	int i = 0;

	vector<Vec3> pointsToTravel;
public:

	Game() {
		camera = new Camera2D();

		//aniTest.test();

		//objs = aniTest.getObjs();


		points.push_back(Vec3(0.0, 0.0,   30.0));  
		points.push_back(Vec3(1.0, 3.5,   30.0    ));  
		points.push_back(Vec3(4.8, 1.8,   30.0    ));  
		points.push_back(Vec3(6.5, 7.0,   30.0    ));  
		points.push_back(Vec3(9.0, 3.5,   30.0    ));  
		points.push_back(Vec3(32.5, 4.8,  30.0   )); 
		points.push_back(Vec3(33.2, 2.6,  30.0   )); 
		points.push_back(Vec3(36.8, 7.0,  30.0   )); 
		points.push_back(Vec3(37.8, 5.0,  30.0   )); 
		points.push_back(Vec3(41.2, 20.5, 30.0  ));
		points.push_back(Vec3(41.5, 21.5, 30.0  ));

		
		curve->set_steps(100); // generate 100 interpolate points between the last 4 way points

		for (Vec3 point : points) {
			curve->add_way_point(Vector(point.x,point.y,point.z));
		}


		float totalDist = getTotalDist();
		float sD = totalDist / 50;
		

		pointsToTravel.push_back(Vec3(curve->node(0).x, curve->node(0).y,30));

		float disc = 0;
		for (int i = 0; i < curve->node_count() - 1; i++) {

			float d = Utils::distance(Vec2(curve->node(i).x, curve->node(i).y), Vec2(curve->node(i + 1).x, curve->node(i + 1).y));
			disc += d;
			if (disc >= sD) {
				disc = 0;
				pointsToTravel.push_back(Vec3(curve->node(i).x, curve->node(i).y, 30));
			}
		}



		sphereX = curve->node(i).x;
		sphereY = curve->node(i).y;
	}

	float getTotalDist() {
		float d = 0;
		for (int i = 0; i < curve->node_count() - 1; i++) {

			d += Utils::distance(Vec2(curve->node(i).x, curve->node(i).y), Vec2(curve->node(i + 1).x, curve->node(i + 1).y));
		}
		return d;
	}


	void update(float deltaTime) {

		if (countTime >= 0) {
			countTime = 0;
			keyTime += 1;
		}

		tesetTime += deltaTime;

		//float pX = Utils::lerp(keyFrame.positionX, nextKeyFrame.positionX, (float)curTime / (float)5);


		//cout << tesetTime << "\n";
		if (tesetTime >= 0.1) {
			tesetTime = 0;
			sphereX = pointsToTravel[i].x;
			sphereY = pointsToTravel[i].y;
			i+= 1;
			if (i >= pointsToTravel.size()) {
				i = 0;
			}
		}
	}
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {
		
	}

	void draw() {


	/*	for (Vec3 point : points) {
			Shapes::drawPoint(point.x,point.y,point.z);
		}*/
		

		// for draw curve

		for (int i = 0; i < curve->node_count() - 1; i++) {
			Shapes::drawLine( curve->node(i).x, curve->node(i).y, curve->node(i + 1).x, curve->node(i + 1).y);
		}

		glLineWidth(1);
		Shapes::drawSpere(sphereX, sphereY, 30, 3.0f);

		
	}
};