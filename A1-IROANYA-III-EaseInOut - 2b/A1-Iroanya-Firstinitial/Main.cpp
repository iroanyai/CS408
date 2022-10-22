#include "GameWindow.h"
#include <iostream>
#include <time.h>
#include "AnimationTest.h"

GameWindow* window;

void update() {
    window->update();
}

void special(int special_key, int x, int y) {
    window->special(special_key, x, y);
}
void onKeyDown(unsigned char key, int x, int y) {
    window->onKeyDown(key, x, y);
}
void onKeyUp(unsigned char key, int x, int y) {
    window->onKeyUp(key, x, y);
}
void reshape(int x,int y) {
    window->reshape(x,y);
}
void idle() {
    glutPostRedisplay();  
}

void timer(int value) {
    glutPostRedisplay();   
    glutTimerFunc(1000/60, timer, 0); // 60 fps
}

// Main
int main(int argc, char* argv[])
{
    srand(time(NULL));




    glutInit(&argc, argv); 
    window = new GameWindow();
   
    window->init(
        update,
        special,
        onKeyDown,
        onKeyUp,
        reshape,
        idle,
        timer);


    window->start();
                       
                               
    return 0;
}
