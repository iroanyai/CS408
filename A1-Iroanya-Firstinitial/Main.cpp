#include "GameWindow.h"


GameWindow* window;

void update() {
    window->update();
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
    glutTimerFunc(30, timer, 0);
}

// Main
int main(int argc, char* argv[])
{
    glutInit(&argc, argv); 
    window = new GameWindow();
   
    window->init(
        update,
        onKeyDown,
        onKeyUp,
        reshape,
        idle,
        timer);


    window->start();
                       
                               
    return 0;
}
