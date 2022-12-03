//
//  Main.h
//

#ifndef MAIN_H
#define MAIN_H



void init ();

void mouseMotion (int x, int y);
void keyboardPressed (unsigned char key, int x, int y);
void keyboardReleased (unsigned char key, int x, int y);
void specialKeyPressed (int key, int x, int y);
void specialKeyReleased (int key, int x, int y);

void handleInput();
void schedule();
void idle ();
void reshape (int w, int h);

void display ();
void drawPole ();
void drawParticleSource ();
void drawText ();

#endif
