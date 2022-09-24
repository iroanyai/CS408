#pragma once
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <cmath>
#include "Vec.h"

class Shapes {

public:
	
    static void drawText(double x,double y,const char* text, Color c = Color(1,1,1)) {
        glRasterPos2i(x, y);
        glColor4f(c.r,c.g,c.b,c.a);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text);
    }

    static void drawRect(Rect r,Color c) {
        glPushMatrix();  
        glTranslatef(r.x, r.y, 0.0f);  
        glBegin(GL_QUADS);   
        glColor4f(c.r,c.g,c.b,c.a); 
        glVertex2f(0, 0);           
        glVertex2f(0,r.h);
        glVertex2f(r.w, r.h);
        glVertex2f(r.w, 0);
        glEnd();
        glPopMatrix();
    }
};