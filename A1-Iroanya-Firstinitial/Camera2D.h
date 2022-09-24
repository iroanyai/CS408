#include <GL/glut.h>
#include "Vec.h"
#include "GameObject.h"

class Camera2D {

	Rect* rect;

public:
	Camera2D() {
		rect = new Rect(0, 0, 1280, 720);
	}

	Rect* getRect() {
		return rect;
	}

	//void follow(GameObject* obj) {

	//	Rect objRect = obj->getRect();

	//	//printf("%f - %f \n", rect->x, rect->w);
	//	if (objRect.x + objRect.w < rect->x) {
	//		//rect->w = rect->w - 1280;
	//		rect->x  = rect->x - 1280;
	//		updateCamera();
	//	}
	//	else if (objRect.x  > rect->x + rect->w) {
	//		//rect->w = rect->w + 1280;
	//		rect->x = rect->x + 1280;
	//		updateCamera();
	//	}
	//	
	//}
	//void updateCamera() {
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	//printf("%f - %f \n", rect->x, rect->w);
	//	//Rect rcopy = rect;
	//	gluOrtho2D(rect->x, rect->x + rect->w, rect->h, rect->y);
	//}

	void draw() {

		Shapes::drawText(rect->x + 5, 30, "'G' - change green");

	}

};