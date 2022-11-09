#pragma once
#include <GL/glut.h>
#include <cmath>
#include "Shapes.h"
#include <iostream>
#include "Game.h"
#include <cassert>

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
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(1024, 768);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("CS408: Person");
		glutKeyboardFunc(onKeyDownCallBack);
		glutIdleFunc(idle);
		glutReshapeFunc(reshape);
		glutDisplayFunc(updateCallBack);

		initt();


		//initGL(); use this for light
		glutMainLoop();
	}

	void initt()
	{
		GLfloat mat_ambient[] = { 0.2,  0.4,  0.2,  1.0 };
		GLfloat mat_diffuse[] = { 0.8,  0.4,  0.4,  1.0 };
		GLfloat mat_specular[] = { 0.5,  0.5,  1.0,  1.0 };
		GLfloat lm_ambient[] = { 0.25, 0.25, 0.25, 1.0 };

		//  select clearing (background) color
		glClearColor(0.0, 0.0, 0.0, 0.0);

		//  initialize viewing values
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		glShadeModel(GL_FLAT);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glPointSize(1.0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);

		glutPostRedisplay();
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


	//void reshape(int WIDTH,int HEIGHT) {
	//	
	//	toOrtho();
	//}

	void idle()
	{
		double waste_time; // in seconds

		for (int i = 0; i < LIMBCOUNT; i++)
		{
			theta[i] += delta[i];
			if ((theta[i] > 45.0) || (theta[i] < 0.0))
				delta[i] = -delta[i];
		}

		// wait until time for next frame
		waste_time = (g_next_frame_time - glutGet(GLUT_ELAPSED_TIME)) / 1000.0;
		if (SHOW_FPS) {
			std::cout << "Waste time in frame =  " << waste_time << " seconds " << std::endl;
		}
		if (waste_time > 0.0)
			Sleep(10);

		// calculate real frame rate
		g_fps = 1000.0 / (float(glutGet(GLUT_ELAPSED_TIME) - g_next_frame_time) + 1000.0 / TARGET_FPS);

		// update time to draw next frame
		g_next_frame_time = glutGet(GLUT_ELAPSED_TIME) + 1000.0 / TARGET_FPS;

		// draw next frame
		glutPostRedisplay();
	}

	void reshape(int w, int h)
	{
		// void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
		glViewport(0, 0, w, h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far);
		gluPerspective(45.0, (GLdouble)w / (GLdouble)h, NEAR_CLIP, FAR_CLIP);
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
		

		GLfloat light_direction[] = { 1.0, 1.0, 1.0, 0.0 };

		static double s_angle_around = 0.0;
		static double s_height = 0.0;
		static double s_height_delta = 12.0;

		unsigned int error = glGetError();

		if (error != 0)
		{
			cout << "OpenGL Error: " << error << endl;
			assert(error == 0);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// set up the camera
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLightfv(GL_LIGHT0, GL_POSITION, light_direction);

		// moving camera
		//gluLookAt(
		//	// looking from:
		//	cos(s_angle_around) * 40, s_height, sin(s_angle_around) * 40,
		//	// looking at:
		//	0.0, 0.0, 0.0,
		//	// vector pointing up from camera 
		//	// (to orient it right-side up):
		//	0.0, 1.0, 0.0);

		 //still camera for screenshots
		gluLookAt(5.0, 20.0, 40.0,
			0.0, -5.0, 0.0,
			0.0, 1.0, 0.0);



		game->update(dt);
		game->draw();

		s_angle_around += 0.5 / g_fps;
		s_height += s_height_delta / g_fps;
		if (s_height <= -25.0 || s_height >= 30.0)
			s_height_delta = -s_height_delta;

		glutSwapBuffers();

	}

	void start() {
		glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		old_t = glutGet(GLUT_ELAPSED_TIME);
	}

};