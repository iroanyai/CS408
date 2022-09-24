#pragma once
#include"Vec.h"
#include "Shapes.h"
class GameObject {
	
protected:
	Vec2 pos;
	Vec2 size;
	Vec2 vel;
	Vec2 acc;

	int speed = 1;

	Color color;
	float lifeTime = 1;
public:
	
	GameObject(Vec2 pos,Vec2 size,Color color) {
		this->pos = pos;
		this->size = size;
		this->color = color;
	}


	void applyForce(Vec2 f) {
		acc = Vec2(acc.x + f.x, acc.y + f.y);
	}

	void init() {

	}

	void update() {
		vel = Vec2(vel.x + acc.x,vel.y + acc.y);
		pos = Vec2(pos.x + vel.x,pos.y + vel.y );
		acc = Vec2(0, 0);
	}

	void draw() {
		Shapes::drawRect(Rect(pos.x,pos.y,size.x,size.y),color);
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

	bool onCollision(GameObject* obj) {
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