#include <GL/glut.h>
#include "Vec.h"

class Camera2D {

	Rect* rect;

public:
	Camera2D() {
		rect = new Rect(0, 0, 1280, 720);
	}

	Rect* getRect() {
		return rect;
	}

	void draw() {

	}

};