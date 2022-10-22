#pragma once
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <cmath>
#include "Vec.h"
#include "Sphere.h"

class Shapes {

public:


    static void drawPoint(float x,float y,float z) {
        glBegin(GL_POINTS);
        glColor4f(1,1,1,1);
        glVertex3f(x,y,z);
        glEnd();
    }

    static void drawLine(float x1, float y1, float x2, float y2) {
        glLineWidth(4);
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(0.0f, 0.0f, 1.f);
        glBegin(GL_LINES);
        glVertex3f(x1,y1,30);
        glVertex3f(x2,y2,30);
        glEnd();
        glDisable(GL_COLOR_MATERIAL);
    }

    static void drawSpere(float x,float y,float z,float radius) {
        Sphere sphere = Sphere(radius, 36, 18);

        // line color
        float lineColor[] = { 0.6f, 0.6f, 0.2f, 1 };
        // draw centre smooth sphere with line
        glPushMatrix();
        glTranslatef(x, y, z);
        glRotatef(0, 1, 0, 0);
        glRotatef(0, 0, 1, 0);
        float static a = 1;
        a += 1;
        glRotatef(a, 1, 1, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        sphere.drawWithLines(lineColor);
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
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