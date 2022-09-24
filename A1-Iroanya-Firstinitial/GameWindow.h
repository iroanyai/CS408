#pragma once
#include <GL/glut.h>
#include <cmath>
#include "Shapes.h"
#include <iostream>
#include "Game.h"

using namespace std;

class GameWindow {
	int x = 2;
	Game *game;
public:
	int WIDTH, HEIGHT;

	GameWindow() {
        WIDTH = 1280, HEIGHT = 720;
		glutInitWindowPosition(
			(int)(glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2,
			(int)(glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2); 
		glutInitWindowSize(WIDTH, HEIGHT);                       
		glutCreateWindow("Trauma Game");       
	}

	void init(void (*updateCallBack)(void), 
		void (*onKeyDownCallBack)(unsigned char , int , int ),
		void (*onKeyUpCallBack)(unsigned char, int, int), 
		void (*reshape)(int, int),
		void(*idle)(void), void(*timer)(int)) {

		game = new Game();

		glEnable(GL_BLEND); //Enable blending.
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glutIdleFunc(idle);
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
        glutDisplayFunc(updateCallBack);
		glutKeyboardFunc(onKeyDownCallBack);
		glutKeyboardUpFunc(onKeyUpCallBack);
		glutReshapeFunc(reshape);
		glutTimerFunc(0, timer, 0);
        glutMainLoop();

	}

	void reshape(int WIDTH,int HEIGHT) {
		// Compute aspect ratio of the new window
		if (HEIGHT == 0) HEIGHT = 1;                // To prevent divide by 0
		GLfloat aspect = (GLfloat)WIDTH / (GLfloat)WIDTH;

		int w = 1280;
		int h = 720;

		// Set the viewport to cover the new window
		glViewport(0, 0, WIDTH, HEIGHT);

		// Set the aspect ratio of the clipping area to match the viewport
		glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
		glLoadIdentity();             // Reset the projection matrix
		gluOrtho2D(0 , w, h, 0);
	}

	void onKeyDown(unsigned char key, int x, int y) {
		game->onKeyDown(key);
	}
	void onKeyUp(unsigned char key, int x, int y) {
		game->onKeyUp(key);
	}

	void update() {
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);    
		glLoadIdentity();
		game->update();
		game->draw();
		glutSwapBuffers();
	}

	void start() {
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

};