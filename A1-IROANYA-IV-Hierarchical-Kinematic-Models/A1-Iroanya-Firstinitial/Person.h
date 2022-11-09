#pragma once
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <cmath>
#include "Vec.h"
#include "Sphere.h"


const unsigned int TARGET_FPS = 60;
double g_fps = TARGET_FPS;
int g_next_frame_time;
const bool SHOW_FPS = false;

const double NEAR_CLIP = 0.01;
const double FAR_CLIP = 1000;

const float TORSO_RADIUS = 3.0f;
const float TORSO_HEIGHT = 8.0f;
const float NECK_RADIUS = 0.5f;
const float NECK_HEIGHT = 1.0f;
const float HEAD_RADIUS = 1.5f;

const float UPPER_ARM_RADIUS = 1.0f;
const float UPPER_ARM_LENGTH = 5.0f;
const float LOWER_ARM_RADIUS = 1.0f;
const float LOWER_ARM_LENGTH = 4.0;

const float UPPER_LEG_RADIUS = 1.5f;
const float UPPER_LEG_LENGTH = 7.0f;
const float LOWER_LEG_RADIUS = 1.5f;
const float LOWER_LEG_LENGTH = 6.0f;

const float FEET_RADIUS = 2.0f;
const float FEET_LENGTH = 1.0f;

const float NOSE_RADIUS = 0.5f;
const float NOSE_LENGTH = 0.5f;

const float EAR_RADIUS = 0.5f;
const float EAR_LENGTH = 0.5f;

const float EYE_RADIUS = 0.3f;
const float EYE_LENGTH = 0.3f;

// bone identifiers (bone ids)
const int LIMB_TORSO = 0;
const int LIMB_NECK = 1;
const int LIMB_HEAD = 2;
const int LIMB_UPPER_LEFT_ARM = 3;
const int LIMB_UPPER_LEFT_LEG = 4;
const int LIMB_LOWER_LEFT_ARM = 5;
const int LIMB_LOWER_LEFT_LEG = 6;

const int LIMB_UPPER_RIGHT_ARM = 7;
const int LIMB_LOWER_RIGHT_ARM = 8;

const int LIMB_UPPER_RIGHT_LEG = 9;
const int LIMB_LOWER_RIGHT_LEG = 10;

const int LIMB_LEFT_FEET = 11;
const int LIMB_RIGHT_FEET = 12;

const int LIMBCOUNT = 13;

// initial angle for all bones (in degrees)
float theta[LIMBCOUNT] =
{
	 0.0, 10.0, 15.0, 20.0,
	30.0, 21.0, 11.0,

	20.0,40.0f,
	20.0,20.0,

	// feet
	1.0,1.0

};

// amount by which each bone rotates per frame (in degrees)
float delta[LIMBCOUNT] =
{
	0.2f, 0.4f, 0.6f, 0.8f,
	1.2f, 1.6f, 2.0f,

	1.2f,1.2f,
	1.0,1.0,

	//feet
	0.0,0.0
};

class Person
{
public:
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


	void display_cylinder(
		GLdouble radius, GLdouble height,
		GLint slices, GLint stacks)
	{
		// Quadrics are used by the GLU library for many
		// 3D shapes
		GLUquadricObj* p = gluNewQuadric();

		// Use a disk to make the bottom of the cylinder.
		// The default disk is vertical facing positive Z-axis,
		// so rotate it around the Y-axis to make it face
		// the other way
		glPushMatrix();
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		gluDisk(p, 0.0, radius, slices, stacks);
		glPopMatrix();

		// main part of cylinder
		gluCylinder(p, radius, radius, height, slices, stacks);

		// Use another disk to make the top of cylinder; 
		// put it out along the positive Z-axis
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, height);
		gluDisk(p, 0.0, radius, slices, stacks);
		glPopMatrix();

		gluDeleteQuadric(p);
	}

	void display_torso()
	{
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		display_cylinder(TORSO_RADIUS, TORSO_HEIGHT, 60, 15);
		glPopMatrix();
	}


	// Display the neck in the same manner as the torso
	void display_neck()
	{
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		display_cylinder(NECK_RADIUS, NECK_HEIGHT, 60, 15);
		glPopMatrix();
	}

	// Display the head as a sphere elongated along the Y-axis
	void display_head()
	{
		glPushMatrix();
		glScalef(1.0, 1.3, 1.0);
		glutSolidSphere(HEAD_RADIUS, 40, 40);
		glPopMatrix();
	}

	// Display the upper arm as a cylinder turned to face along 
	// the positive X-axis (the figure's left arm) by rotating
	// around the Y axis.
	void display_upper_arm()
	{
		glPushMatrix();
		glRotatef(90.0, 0.0, 1.0, 0.0);
		display_cylinder(UPPER_ARM_RADIUS, UPPER_ARM_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_lower_arm()
	{
		glPushMatrix();
		glRotatef(90.0, 0.0, 1.0, 0.0);
		display_cylinder(LOWER_ARM_RADIUS, LOWER_ARM_LENGTH, 15, 15);
		glPopMatrix();
	}

	// Display the upper leg as a cylinder turned to face along 
	// the negative Y-axis (projecting downward) by rotating
	// around the X-axis.
	void display_upper_leg()
	{
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		display_cylinder(UPPER_LEG_RADIUS, UPPER_LEG_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_lower_leg()
	{
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		display_cylinder(LOWER_LEG_RADIUS, LOWER_LEG_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_feet() {
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		display_cylinder(FEET_RADIUS, FEET_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_nose() {
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		display_cylinder(NOSE_RADIUS, NOSE_LENGTH, 15, 15);
		glPopMatrix();
	}
	void display_ear() {
		glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		display_cylinder(EAR_RADIUS, EAR_LENGTH, 15, 15);
		glPopMatrix();
	}
	void display_eye() {
		glPushMatrix();
		glRotatef(0.0, 1.0, 0.0, 0.0);
		display_cylinder(EYE_RADIUS, EYE_LENGTH, 15, 15);
		glPopMatrix();
	}

	void display_person()
	{
		// origin is in the middle of torso
		glTranslatef(0.0, -TORSO_HEIGHT / 2.0, 0.0);
		display_torso();

		// neck, head, nose, and ears
		// base of neck is determined relative to the bottom of the
		// torso.
		glPushMatrix();
		glTranslatef(0.0, TORSO_HEIGHT, 0.0);
		glRotatef(theta[LIMB_NECK], 1.0, 0.0, 0.0);
		display_neck();

		glPushMatrix();
		glTranslatef(0.0, NECK_HEIGHT, 0.0);
		glRotatef(theta[LIMB_HEAD], 0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(0.0, HEAD_RADIUS, 0.0); // node transform to compensate for model
		display_head();

			glPushMatrix(); // nose
			glTranslatef(-NOSE_LENGTH/2, 0, 1.2);
			glRotatef(0, 1.0, 0.0, 0.0);
			display_nose();
			glPopMatrix();

			glPushMatrix(); // left ear
			glTranslatef(-HEAD_RADIUS - EAR_RADIUS/2, 0, 0);
			glRotatef(0, 1.0, 0.0, 0.0);
			display_ear();
			glPopMatrix();

			glPushMatrix(); // right ear
			glTranslatef(+HEAD_RADIUS - EAR_RADIUS / 2, 0, 0);
			glRotatef(0, 1.0, 0.0, 0.0);
			display_ear();
			glPopMatrix();

			glPushMatrix(); // left eye
			glTranslatef(-EYE_LENGTH *3, 0.8, 1);
			glRotatef(0, 1.0, 0.0, 0.0);
			display_eye();
			glPopMatrix();

			glPushMatrix(); // right eye
			glTranslatef(EYE_LENGTH * 3, 0.8, 1);
			glRotatef(0, 1.0, 0.0, 0.0);
			display_eye();
			glPopMatrix();

		glPopMatrix();

		glPopMatrix();
		glPopMatrix();

		// left arm
		glPushMatrix();
		glTranslatef(TORSO_RADIUS, TORSO_HEIGHT - UPPER_ARM_RADIUS, 0.0);
		glRotatef(theta[LIMB_UPPER_LEFT_ARM], 0.0, 0.0, 1.0);
		display_upper_arm();

		glPushMatrix();
		glTranslatef(UPPER_ARM_LENGTH, 0.0, 0.0);
		glRotatef(theta[LIMB_LOWER_LEFT_ARM], 0.0, 0.0, 1.0);
		display_lower_arm();
		glPopMatrix();
		glPopMatrix();

		// right arm
		glPushMatrix();
		glTranslatef(-TORSO_RADIUS, TORSO_HEIGHT - UPPER_ARM_RADIUS, 0.0);
		glScalef(-1, 1, 1);
		glRotatef(theta[LIMB_UPPER_RIGHT_ARM], 0.0, 0.0, 1.0);
		display_upper_arm();

		glPushMatrix();
		glTranslatef(UPPER_ARM_LENGTH, 0.0, 0.0);
		glScalef(1, 1, 1);
		glRotatef(theta[LIMB_LOWER_RIGHT_ARM], 0.0, 0.0, 1.0);
		display_lower_arm();
		glPopMatrix();
		glPopMatrix();

		// left leg
		glPushMatrix();
		glTranslatef(TORSO_RADIUS - UPPER_LEG_RADIUS, 0.0, 0.0);
		glRotatef(-theta[LIMB_UPPER_LEFT_LEG], 1.0, 0.0, 0.0);
		display_upper_leg();
			glPushMatrix();
			glTranslatef(0.0, -UPPER_LEG_LENGTH, 0.0);
			glRotatef(theta[LIMB_LOWER_LEFT_LEG], 1.0, 0.0, 0.0);
			display_lower_leg();
				glPushMatrix();
				glTranslatef(0.0, -LOWER_LEG_LENGTH , 0.0);
				glRotatef(theta[LIMB_LEFT_FEET], 1.0, 0.0, 0.0);
				display_feet();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();


		// right leg
		glPushMatrix();
		glTranslatef(TORSO_RADIUS - UPPER_LEG_RADIUS * 3, 0.0, 0.0);
		glScalef(-1, 1, 1);
		glRotatef(-theta[LIMB_UPPER_RIGHT_LEG], 1.0, 0.0, 0.0);
		display_upper_leg();
			glPushMatrix();
			glTranslatef(0.0, -UPPER_LEG_LENGTH, 0.0);
			glRotatef(theta[LIMB_LOWER_RIGHT_LEG], 1.0, 0.0, 0.0);
			display_lower_leg();
				glPushMatrix();
				glTranslatef(0.0, -LOWER_LEG_LENGTH, 0.0);
				glRotatef(theta[LIMB_RIGHT_FEET], 1.0, 0.0, 0.0);
				display_feet();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	}

};

