#pragma once
#include "Vec.h"
#include "Shapes.h"
class Par {

public:
	Vec3 vel;
	Vec3 pos;
	float r;
	Par(Vec3 pos,Vec3 vel, float r) {
		this->pos = pos;
		this->vel = vel;
		this->r = r;
	}

	void draw() {

		pos.x += vel.x;
		pos.y += vel.y;
		pos.z += vel.z;

		//Shapes::drawSpere(pos.x, pos.y, pos.z, r);
	}

};