#pragma once
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <cmath>
#include "Vec.h"


class Shapes {

public:
	
    static void drawPoint(float x, float y, float z,Color color) {
        glColor4f(color.r,color.g,color.b,color.a);
        glBegin(GL_POINTS);
        glVertex3f(x, y, z);
        glEnd();
    }

    static void drawText(double x,double y,const char* text, Color textColor = Color(1, 1, 0.3f, 1)) {
        glColor4f(textColor.r, textColor.g, textColor.b, textColor.a);
        glRasterPos2i(x, y);
        glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)text);
    }

    static void drawRect(Rect r,float pX,float pY,float pZ,float rX, float rY, float rZ, float sX, float sY, float sZ,Color c) {
        static float angle = 0;
        angle += 0.1;
        glPushMatrix();  
        glTranslatef(pX, pY, pZ);  
        glRotatef(angle, rX, rY, rZ);
        glScalef(sX, sY, sZ);
       
        int s = r.w;
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2f(s / 2, s / 2);
        glVertex2f(s / 2, s / 4); // 1
        glVertex2f(s, 0);
        glVertex2f(s - s / 4, s / 2); // 2
        glVertex2f(s, s);
        glVertex2f(s / 2, s - s / 4); //3
        glVertex2f(0, s);
        glVertex2f(s / 4, s / 2); //4
        glVertex2f(0, 0);
        glVertex2f(s / 2, s / 4); //1

        glEnd();
        glPopMatrix();
    }

    static void drawShape1(Rect r, Color c) {
        int s = r.w;
        float value = 0.5;
        glPushMatrix();
        glTranslatef(r.x, r.y, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2f(s/2, s/2);
        glVertex2f(s/2, s/4); // 1
        glVertex2f(s, 0);
        glVertex2f(s - s/4, s/2); // 2
        glVertex2f(s,s);
        glVertex2f(s/2,s-s/4); //3
        glVertex2f(0,s);
        glVertex2f(s/4,s/2); //4
        glVertex2f(0,0);
        glVertex2f(s / 2, s / 4); //1
        glEnd();
        glPopMatrix();
    }

    static void drawShape2(Rect r, Color c) {
        int s = r.w;
        glPushMatrix();
        glTranslatef(r.x, r.y, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2f(s / 2, s / 2);
        glVertex2f(s / 2, 0); // 1
        glVertex2f(s, 0);
        glVertex2f(s, s / 2); // 2
        glVertex2f(s, s);
        glVertex2f(s / 2, s); //3
        glVertex2f(0, s);
        glVertex2f(0, s / 2); //4
        glVertex2f(0, 0);
        glVertex2f(s / 2, 0); //1
        glEnd();
        glPopMatrix();
    }

    static void drawShape3(Rect r, Color c) {
        int s = r.w;
        glPushMatrix();
        glTranslatef(r.x, r.y, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2f(s / 2, s / 2);
        glVertex2f(s / 2, -(s / 4)); // 1
        glVertex2f(s, 0);
        glVertex2f((s + s / 4), s / 2); // 2
        glVertex2f(s, s);
        glVertex2f(s / 2, s + s / 4); //3
        glVertex2f(0, s);
        glVertex2f(-(s / 4), s / 2); //4
        glVertex2f(0, 0);
        glVertex2f(s / 2, -(s / 4)); //1
        glEnd();
        glPopMatrix();
    }


    static void drawShape4(Rect r, Color c) {
        int s = r.w;
        glPushMatrix();
        glTranslatef(r.x, r.y, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2f(s / 2, s / 2);
        glVertex2f(s / 2, -(s / 2)); // 1
        glVertex2f(s, 0);
        glVertex2f((s + s / 2), s / 2); // 2
        glVertex2f(s, s);
        glVertex2f(s / 2, s + s / 2); //3
        glVertex2f(0, s);
        glVertex2f(-(s / 2), s / 2); //4
        glVertex2f(0, 0);
        glVertex2f(s / 2, -(s / 2)); //1
        glEnd();
        glPopMatrix();
    }

    static void drawShape5(Rect r, Color c) {
        int s = r.w;
        glPushMatrix();
        glTranslatef(r.x, r.y, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(c.r, c.g, c.b, c.a);
        glVertex2f(s / 2, s / 2);
        glVertex2f(s / 2, -(s)); // 1
        glVertex2f(s, 0);
        glVertex2f((s + s), s / 2); // 2
        glVertex2f(s, s);
        glVertex2f(s / 2, s + s ); //3
        glVertex2f(0, s);
        glVertex2f(-(s), s / 2); //4
        glVertex2f(0, 0);
        glVertex2f(s / 2, -(s)); //1
        glEnd();
        glPopMatrix();
    }

};