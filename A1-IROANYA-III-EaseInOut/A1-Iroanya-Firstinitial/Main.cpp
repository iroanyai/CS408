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

	cout << "1. normal \n";
    cout << "2. SinusoidalEasein \n";
    cout << "3. SinusoidalEaseout \n";
    cout << "4. ParabolicEasein \n";
    cout << "5. ParabolicEaseout \n";

    char input = 'c';
    while (input == 'c')
    {
	    cout << "Input: ";
	    cin >> input;

	    switch (input)
	    {
	    case '1':
		    Utils::mode = Utils::NORMAL;
		    break;
	    case '2':
            Utils::mode = Utils::SinusoidalEasein;
		    break;
	    case '3':
            Utils::mode = Utils::SinusoidalEaseout;
		    break;
	    case '4':
            Utils::mode = Utils::ParabolicEasein;
		    break;
	    case '5':
            Utils::mode = Utils::ParabolicEaseout;
		    break;
	    }
    }


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
