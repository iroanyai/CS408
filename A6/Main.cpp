//
//  Main.cpp
//

#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "GetGlut.h"
#include "Random.h"
#include "Sleep.h"
#include "ObjLibrary/Vector3.h"
#include "ObjLibrary/SpriteFont.h"

#include "Constants.h"
#include "HeightMap.h"
#include "Main.h"

using namespace std;

namespace
{
	const double FRAME_LENGTH = 1.0 / 60.0;
	int g_previous_time = 0; // milliseconds

	int g_window_width;
	int g_window_height;

	bool ga_key_pressed[128];
	const unsigned int ARROW_COUNT = 4;
	const unsigned int ARROW_UP    = 0;
	const unsigned int ARROW_DOWN  = 1;
	const unsigned int ARROW_LEFT  = 2;
	const unsigned int ARROW_RIGHT = 3;
	bool ga_arrow_pressed[ARROW_COUNT];

	SpriteFont g_sprite_font;
	const Vector3 DEFAULT_CAMERA_POSITION(0.0, 150.0, WORLD_SIZE / 2.0);
	Vector3 g_camera = DEFAULT_CAMERA_POSITION;
	const Vector3 LOOK_AT_POSITION(WORLD_SIZE / 2.0, 50.0, WORLD_SIZE / 2.0);
	Vector3 g_source(LOOK_AT_POSITION + Vector3(0, 400, 0));

	const double CAMERA_INWARD_RATE = 0.995;
	const double CAMERA_TURN_RATE   = PI * 0.001;

	HeightMap g_height_map("Heightmap.txt");
}

int main(int argc, char** argv)
{
	glutInitWindowSize (1024, 768);
	glutInitWindowPosition (0, 0);
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow ("Piling Sand");
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboardPressed);
	glutKeyboardUpFunc(keyboardReleased);
	glutSpecialFunc(specialKeyPressed);
	glutSpecialUpFunc(specialKeyReleased);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	init ();
	
	glutMainLoop();
	
	return 0;   // ISO C requires main to return int.
}

void init ()
{
//  select clearing (background) color
	glClearColor (0.0, 0.8, 1.0, 0.0);
//  initialize viewing values
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glutIgnoreKeyRepeat(GL_TRUE);
	glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	seedRandom();
	g_sprite_font.load("FontOcrAExtended24.bmp");

	// LOAD ANY MODELS HERE

	g_previous_time = glutGet(GLUT_ELAPSED_TIME); // in milliseconds

	glutPostRedisplay();
}



void mouseMotion (int x, int y)
{
	;
}

void keyboardPressed (unsigned char key, int x, int y)
{
	if(key >= 'a' && key <= 'z')
		key = key - 'a' + 'A';
	ga_key_pressed[key] = true;

	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void keyboardReleased (unsigned char key, int x, int y)
{
	if(key >= 'a' && key <= 'z')
		key = key - 'a' + 'A';
	ga_key_pressed[key] = false;
}

void specialKeyPressed (int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ga_arrow_pressed[ARROW_UP] = true;
		break;
	case GLUT_KEY_DOWN:
		ga_arrow_pressed[ARROW_DOWN] = true;
		break;
	case GLUT_KEY_RIGHT:
		ga_arrow_pressed[ARROW_RIGHT] = true;
		break;
	case GLUT_KEY_LEFT:
		ga_arrow_pressed[ARROW_LEFT] = true;
		break;
	}
}

void specialKeyReleased (int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		ga_arrow_pressed[ARROW_UP] = false;
		break;
	case GLUT_KEY_DOWN:
		ga_arrow_pressed[ARROW_DOWN] = false;
		break;
	case GLUT_KEY_RIGHT:
		ga_arrow_pressed[ARROW_RIGHT] = false;
		break;
	case GLUT_KEY_LEFT:
		ga_arrow_pressed[ARROW_LEFT] = false;
		break;
	}
}


void handleInput()
{
	Vector3 offset = g_camera - LOOK_AT_POSITION;
	if(ga_key_pressed['I'])
	{
		offset.x *= CAMERA_INWARD_RATE;
		offset.z *= CAMERA_INWARD_RATE;
	}
	if(ga_key_pressed['O'])
	{
		offset.x /= CAMERA_INWARD_RATE;
		offset.z /= CAMERA_INWARD_RATE;
	}
	if(ga_arrow_pressed[ARROW_LEFT])
	{
		offset.rotateY(-CAMERA_TURN_RATE);
	}
	if(ga_arrow_pressed[ARROW_RIGHT])
	{
		offset.rotateY(CAMERA_TURN_RATE);
	}
	if(ga_arrow_pressed[ARROW_UP])
	{
		offset += Vector3(0, 1, 0);
	}
	if(ga_arrow_pressed[ARROW_DOWN])
	{
		offset += Vector3(0, -1, 0);
	}
	g_camera = LOOK_AT_POSITION + offset;

	if(ga_key_pressed['R'])
	{
		g_camera = DEFAULT_CAMERA_POSITION;
	}

	Vector3 camera_direction = -offset; 
	camera_direction.y = 0;
	camera_direction.normalize(); 

	if(ga_key_pressed['W'])
	{
		// move source of sand away from us
		g_source += camera_direction;
	}
	if(ga_key_pressed['S'])
	{
		// move source of sand towards us
		g_source -= camera_direction;
	}

	if(ga_key_pressed['A'])
	{
		// move source of sand left
		g_source += camera_direction.getRotatedY(PI / 2);
	}

	if(ga_key_pressed['D'])
	{
		// move source of sand right
		g_source -= camera_direction.getRotatedY(PI / 2);
	}
}



void schedule ()
{
	int current_time = glutGet(GLUT_ELAPSED_TIME); // in milliseconds
	int elapsed_time = current_time - g_previous_time; // in milliseconds

	if(elapsed_time < FRAME_LENGTH)
		sleep(FRAME_LENGTH - elapsed_time);

	g_previous_time = current_time;
}

void idle ()
{
	handleInput();

	// UPDATES

	schedule();

	// draw next frame
	glutPostRedisplay();
}

void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)(w) / (GLdouble)(h), 0.1, 2000.0);

	g_window_width = w;
	g_window_height = h;

	glMatrixMode(GL_MODELVIEW);
}

void display ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(g_camera.x,         g_camera.y,        g_camera.z,			// camera position
			  LOOK_AT_POSITION.x, g_camera.y - 50.0, LOOK_AT_POSITION.z, 				// look at point
			  0.0,                1.0,               0.0);						// up vector

	g_height_map.draw();
	drawPole();
	drawParticleSource();

	drawText();

	glFlush (); 
	glutSwapBuffers();
}

void drawPole ()
{
	glLineWidth(3.0f);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(LOOK_AT_POSITION.x,   0.0f, LOOK_AT_POSITION.z);
		glVertex3f(LOOK_AT_POSITION.x, 100.0f, LOOK_AT_POSITION.z);
	glEnd();
}

void drawParticleSource ()
{
	glColor3f(0.6, 0.4, 0.2);
	glPushMatrix();
		glTranslated(g_source.x, g_source.y, g_source.z);
		glutSolidSphere(10.0, 16, 12);
	glPopMatrix();

}

void drawText ()
{
	stringstream camera_string_stream;
	camera_string_stream << fixed << setprecision(1) << "Camera: " << g_camera;
	
	SpriteFont::setUp2DView(g_window_width, g_window_height);
	g_sprite_font.draw(camera_string_stream.str(), 32, 64, 0xFF, 0xFF, 0xFF);
	SpriteFont::unsetUp2DView();
}
