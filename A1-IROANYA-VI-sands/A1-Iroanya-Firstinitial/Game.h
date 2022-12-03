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
#include "Par.h"
#include "TextureBmp.h"

#define PI 3.14159265


class Game {

	Camera2D* camera;
	bool startGame = false;

	//AnimationTest aniTest;

	//vector<Obj*> objs;

	float countTime = 0;
	float keyTime = 0;
	vector<Vec3>* points2;


	double sphereX = 0;
	double sphereY = 0;

	float time = 0;

	Person person;
	TextureBmp texture;
	unsigned char* textureAr;

	vector<Par*> particles;

	int textt;
public:


	Game() {
		camera = new Camera2D();

		points2 = new vector<Vec3>();

		int zz = 50;
		int xx = 50;
		for (int z = -50; z < zz; z++) {
			for (int x = -50; x < xx; x++) {
				float y = 0;

				int x1 = x;
				int z1 = z;
				int x2 = x + 1;
				int z2 = z + 1;

				int y1, y2, y3, y4;
				y1 = y2 = y3 = y4 = 0;
				heightMap(&x1, &x2, &z1, &z2, &y1, &y2, &y3, &y4);


				points2->push_back(Vec3(x1, y1, z1));
				points2->push_back(Vec3(x1, y2, z2));
				points2->push_back(Vec3(x2, y3, z2));
				points2->push_back(Vec3(x2, y4, z1));
			}
		}

		texture.load("sand.bmp");
		textt = texture.addToOpenGL();
		textureAr = texture.getArray();


	}

	void update(float deltaTime) {

		time += deltaTime;
		//printf("%f tim\n", time);
		if (time >= 0){

			time = 0;
			particles.push_back(new Par(Vec3(0,40,0),Vec3(Utils::RandomFloat(-0.1f, 0.1f),-Utils::RandomFloat(0.1f,0.5f), 0), Utils::RandomFloat(0.1f, 0.5f)));
		}
	}
	
	//this function take char input from the user
	void onKeyDown(int key) {

	}
	void onKeyUp(int key) {

	}

	void display_axes()
	{
		// show X, Y, and Z axis in red, green, and blue
		const double AXIS_LENGTH = 60.0;
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glColor3d(1.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(AXIS_LENGTH, 0.0, 0.0);
		glColor3d(0.0, 1.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, AXIS_LENGTH, 0.0);
		glColor3d(0.0, 0.0, 1.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, AXIS_LENGTH);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	void draw() {
		display_axes();

		glBindTexture(GL_TEXTURE_2D, textt);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBegin(GL_QUADS);

		for (int i = 0; i < points2->size();i++) {
			Vec3 p = points2->at(i);
			glVertex3f(p.x, p.y, p.z);
		}

		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisable(GL_TEXTURE_2D);

		// for draw curve
		glLineWidth(1);
		//Shapes::drawSpere(0, 20, 0, 1.0f);
		glPointSize(5);

		glBegin(GL_POINTS);
		for (Par* p : particles) {
			p->draw();
			glVertex3f(p->pos.x, p->pos.y, p->pos.z);
		}
		glEnd();

	}

	void heightMap(int* x1, int* x2, int* z1, int* z2, int* y1, int* y2, int* y3, int* y4) {
		vector<Vec3> h;
		for (int z = -10; z <= -2; z++) {
			for (int x = -10; x < -2; x++) {
				h.push_back(Vec3(x, z, 10));
				h.push_back(Vec3(x, z, 10));
				h.push_back(Vec3(x, z, 10));
				h.push_back(Vec3(x, z, 5));
			}
		}
		for (int z = 0; z <= 8; z++) {
			for (int x = 0; x < 8; x++) {
				h.push_back(Vec3(x, z, 12));
				h.push_back(Vec3(x, z, 8));
				h.push_back(Vec3(x, z, 15));
				h.push_back(Vec3(x, z, 12));
			}
		}

		for (int z = 10; z <= 25; z++) {
			for (int x = -20; x < -10; x++) {
				h.push_back(Vec3(x, z, 3));
				h.push_back(Vec3(x, z, 4));
				h.push_back(Vec3(x, z, 5));
				h.push_back(Vec3(x, z, 6));
			}
		}


		for (Vec3 p : h) {
			if (*x1 == p.x && *z1 == p.y) {
				*y1 = p.z;
			}
			if (*x1 == p.x && *z2 == p.y) {
				*y2 = p.z;
			}
			if (*x2 == p.x && *z2 == p.y) {
				*y3 = p.z;
			}
			if (*x2 == p.x && *z1 == p.y) {
				*y4 = p.z;
			}
		}
	}

};