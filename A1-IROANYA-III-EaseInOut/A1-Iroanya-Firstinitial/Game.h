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

		std::cout << "nodes: " << curve->node_count() << std::endl;
		std::cout << "total length: " << curve->total_length() << std::endl;
		for (int i = 0; i < curve->node_count(); ++i) {
			std::cout << "node #" << i << ": " << curve->node(i).toString() << " (length so far: " << curve->length_from_starting_point(i) << ")" << std::endl;
		}

	}


	void update(float deltaTime) {

	



	}
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {
		
	}

	void draw() {

		glLineWidth(1);
		//Shapes::drawSpere(points[0].x, points[0].y, points[0].z, 5.0f);

		//Shapes::drawPoint(30,30,30);
		//Shapes::drawPoint(points[0].x, 30, 30);


		for (Vec3 point : points) {
			Shapes::drawPoint(point.x,point.y,point.z);
		}
		
		// for draw curve

		for (int i = 0; i < curve->node_count() - 1; i++) {
			//glVertex3f(curve->node(i).x, curve->node(i).y, curve->node(i).z);
			
			Shapes::drawLine( curve->node(i).x, curve->node(i).y, curve->node(i + 1).x, curve->node(i + 1).y);

		}
		
	}
};