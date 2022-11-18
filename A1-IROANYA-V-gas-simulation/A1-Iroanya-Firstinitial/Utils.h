#pragma once
#include "iostream"
#include "Vec.h"
#include<sstream>

class Utils {

public:

    template <size_t N>
    static void splitString(string(&arr)[N], string str)
    {
        int n = 0;
        istringstream iss(str);
        for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
            arr[n] = *it;
    }
    static float lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }


    static int limitNum(int min, int max, int value) {
        if (value <= min) {
            value = min;
        }
        if (value >= max) {
            value = max;
        }
        return value;
    }
    static float limitNum(float min, float max, float value) {
        if (value <= min) {
            value = min;
        }
        if (value >= max) {
            value = max;
        }
        return value;
    }

    static int randRange(int min ,int max) {
        return  rand() % (max - min + 1) + min;
    }

    static float vectorLength(Vec2 v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    static Vec2 normalizeVector(Vec2 v) {
        float length = vectorLength(v);
        return Vec2(v.x / length, v.y / length);
    }
    static float RandomFloat(float a, float b) {
        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }
    static float distance(Vec2 p1, Vec2 p2)
    {
        // Calculating distance
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0);
    }
};
