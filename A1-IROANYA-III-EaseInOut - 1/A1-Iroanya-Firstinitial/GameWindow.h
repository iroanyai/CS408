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
	float old_t;
	const float CAMERA_DISTANCE = 4.0f;

	float cameraAngleX = 0;
	float cameraAngleY = 0;

public:
	int WIDTH, HEIGHT;

	GameWindow() 
	{
		WIDTH = 1280, HEIGHT = 720;

       /* WIDTH = 1280, HEIGHT = 720;
		glutInitWindowPosition(
			(int)(glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2,
			(int)(glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2); 
		glutInitWindowSize(WIDTH, HEIGHT);                       
		glutCreateWindow("Animation test");       */
	}

	void init(void (*updateCallBack)(void), 
		void (*special)(int, int, int),
		void (*onKeyDownCallBack)(unsigned char , int , int ),
		void (*onKeyUpCallBack)(unsigned char, int, int), 
		void (*reshape)(int, int),
		void(*idle)(void), void(*timer)(int)) {


		//glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);   // display mode

		glutInitWindowSize(WIDTH, HEIGHT);  // window size

		glutInitWindowPosition(100, 100);               // window location

		// finally, create a window with openGL context
		// Window will not displayed until glutMainLoop() is called
		// it returns a unique ID
		int handle = glutCreateWindow("Anime");     // param is the title of window

		// register GLUT callback functions
		//glutDisplayFunc(displayCB);
		//glutTimerFunc(33, timerCB, 33);             // redraw only every given millisec
		//glutReshapeFunc(reshapeCB);
		//glutKeyboardFunc(keyboardCB);



	/*	glutMouseFunc(mouseCB);
		glutMotionFunc(mouseMotionCB);*/

		glPointSize(10);

		game = new Game();


		//glutIdleFunc(idle);
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
        glutDisplayFunc(updateCallBack);
		glutKeyboardFunc(onKeyDownCallBack);
		glutSpecialFunc(special);
		glutKeyboardUpFunc(onKeyUpCallBack);
		glutReshapeFunc(reshape);
		glutTimerFunc(0, timer, 0);

		//initGL(); use this for light
		glutMainLoop();

	}

	void initGL()
	{
		glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

		// enable /disable features
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_CULL_FACE);


		// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
		//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		//glEnable(GL_COLOR_MATERIAL);

		glClearColor(0, 0, 0, 0);                   // background color
		glClearStencil(0);                          // clear stencil buffer
		glClearDepth(1.0f);                         // 0 is near, 1 is far
		glDepthFunc(GL_LEQUAL);

		initLights();
	}

	void initLights()
	{
		// set up light colors (ambient, diffuse, specular)
		GLfloat lightKa[] = { .3f, .3f, .3f, 1.0f };  // ambient light
		GLfloat lightKd[] = { .7f, .7f, .7f, 1.0f };  // diffuse light
		GLfloat lightKs[] = { 1, 1, 1, 1 };           // specular light
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

		// position the light
		float lightPos[4] = { 0, 0, 1, 0 }; // directional light
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

		glEnable(GL_LIGHT0);                        // MUST enable each light source after configuration
	}


	void reshape(int WIDTH,int HEIGHT) {
		// Compute aspect ratio of the new window
		//if (HEIGHT == 0) HEIGHT = 1;                // To prevent divide by 0
		//GLfloat aspect = (GLfloat)WIDTH / (GLfloat)WIDTH;

		//int w = 1280;
		//int h = 720;

		//// Set the viewport to cover the new window
		////glViewport(0, 0, WIDTH, HEIGHT);

		//glMatrixMode(GL_PROJECTION);  
		//glLoadIdentity();            
		////gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
		//glLoadIdentity();
		//glOrtho(-WIDTH/2, WIDTH/2, HEIGHT/2, -HEIGHT/2, 1000, -1000);
		//glMatrixMode(GL_MODELVIEW);
		//glEnable(GL_DEPTH_TEST);

		/*screenWidth = w;
		screenHeight = h;*/
		toOrtho();
		//std::cout << "window resized: " << w << " x " << h << std::endl;
	}

	void toOrtho()
	{
		
		int width = 100;
		int heigh = 100;

		// set viewport to be the entire window
		glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

		// set orthographic viewing frustum
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-width/2, width/2, heigh/2, -heigh/2, 1, -1000);

		// switch to modelview matrix in order to set scene
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}


	void toPerspective()
	{
		// set viewport to be the entire window
		glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

		// set perspective viewing frustum
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//gluPerspective(40.0f, (float)(WIDTH) / HEIGHT, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

		// switch to modelview matrix in order to set scene
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}


	void special(int special_key, int x, int y) {
	}
	void onKeyDown(unsigned char key, int x, int y) {
		game->onKeyDown(key);
	}
	void onKeyUp(unsigned char key, int x, int y) {
		game->onKeyUp(key);
	}

	void update() {
		int t;
		float dt;
		t = glutGet(GLUT_ELAPSED_TIME);
		dt = (t - old_t) / 1000.0;
		old_t = t;
		//printf("delta time : %f\n", dt);

		//glClearColor(0.01f, 0.01f, 0.01f, 0.3f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//glMatrixMode(GL_MODELVIEW);    
		//glLoadIdentity();

		//glutSwapBuffers();


		// clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(0.3f, 0.3f, 0.3f, 0.3f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		// save the initial ModelView matrix before modifying ModelView matrix
		glPushMatrix();

		// tramsform modelview matrix
		glTranslatef(0, 0, -CAMERA_DISTANCE);

		// set material
		float ambient[] = { 0.5f, 0.5f, 0.5f, 1 };
		float diffuse[] = { 0.7f, 0.7f, 0.7f, 1 };
		float specular[] = { 1.0f, 1.0f, 1.0f, 1 };
		float shininess = 128;
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
		
		game->update(dt);
		game->draw();

		//showInfo();     // print max range of glDrawRangeElements

		glPopMatrix();

		glutSwapBuffers();

	}

	void start() {
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		old_t = glutGet(GLUT_ELAPSED_TIME);
	}

};