#pragma once
#include<iostream>
using namespace std;

struct Vec2 {
	float x;
	float y;

	Vec2(){
		x = y = 0;
	}
	Vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

struct Vec3 {
	float x;
	float y;
	float z;

	Vec3() {
		x = y = z = 0;
	}
	Vec3(float x, float y ,float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};


struct Color {
	float r, g, b,a;

	Color(){
		r = g = b = a = 0;
	}
	Color(float r, float g, float b,float a = 1) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};


struct Rect {
	float x;
	float y;
	float w;
	float h;

	Rect(){
		x = y = w = h = 0;
	}
	Rect(float x, float y, float w, float h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};