#pragma once
#include"Vec.h"
#include "Shapes.h"
class Particle {
	
protected:
	Vec2 pos;
	Vec2 size;
	Vec2 vel;
	Vec2 acc;

	int speed = 1;

	Color color;
	float lifeTime = 1;

	Vec2 force;
	float shape;
public:
	
	Particle(Vec2 pos,Vec2 size,Color color,Vec2 force,float shape) {
		this->pos = pos;
		this->size = size;
		this->color = color;

		this->force = force;
		this->shape = shape;
	}


	void applyForce(Vec2 f) {
		acc = Vec2(acc.x + f.x, acc.y + f.y);
	}

	void init() {

	}

	void update(float dt) {
		lifeTime -= dt;

		vel = Vec2(vel.x + acc.x,vel.y + acc.y);
		pos = Vec2(pos.x + vel.x * dt,pos.y + vel.y * dt );
		acc = Vec2(0, 0);
	}

	bool isDead() {
		return lifeTime <= 0;
	}

	void draw() {
		printf("shape : %f \n", shape);
		if (shape == 0.5) {
			Shapes::drawShape1(Rect(pos.x, pos.y, size.x, size.y), color);
		}
		if (shape == 1) {
			Shapes::drawShape2(Rect(pos.x, pos.y, size.x, size.y), color);
		}
		if (shape == 1.5) {
			Shapes::drawShape3(Rect(pos.x, pos.y, size.x, size.y), color);
		}
		if (shape == 2) {
			Shapes::drawShape4(Rect(pos.x, pos.y, size.x, size.y), color);
		}
		if (shape == 3) {
			Shapes::drawShape5(Rect(pos.x, pos.y, size.x, size.y), color);
		}
	}
	
	Vec2 getForce() {
		return force;
	}

	void setPos(Vec2 pos) {
		this->pos = pos;
	}
	Vec2 getPos() {
		return pos;
	}
	void setVel(Vec2 vel) {
		this->vel = vel;
	}
	Vec2 getVel() {
		return vel;
	}

	Rect getRect() {
		return Rect(pos.x, pos.y, size.x, size.y);
	}

	bool onCollision(Particle* obj) {
		Rect rect = obj->getRect();
		Rect r = getRect();
		if (r.x < rect.x + rect.w &&
			r.x + r.w > rect.x &&
			r.y < rect.y + rect.h &&
			r.h + r.y > rect.y) {
			return true;
		}
		return false;
	}

};