#pragma once
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <math.h>
#include "Vector2D.h"
const float PIXELS_PER_METER = 50.0f; // 예: 30px = 1m
const float SCREEN_HEIGHT = 800.0f;

// 회전 변환 함수 (라디안 단위)
inline  void rotatePoint(float x, float y, float cx, float cy, float theta, float& outX, float& outY) {
    float dx = x - cx;
    float dy = y - cy;
    outX = cx + dx * std::cos(theta) - dy * std::sin(theta);
    outY = cy + dx * std::sin(theta) + dy * std::cos(theta);
}

// 사용 예: 선분 (x1, y1)와 (x2, y2)를 중심 (cx, cy)에서 θ 만큼 회전
inline  void rotateLineSegment(float x1, float y1, float x2, float y2,
                       float cx, float cy, float theta,
                       float& outX1, float& outY1, float& outX2, float& outY2)
{
    rotatePoint(x1, y1, cx, cy, theta, outX1, outY1);
    rotatePoint(x2, y2, cx, cy, theta, outX2, outY2);
}

inline float toRadian(float angle){
	float radian = angle*(M_PI / 180.0f);
    return radian;
}

inline void toRadian(float angle, float& radian){
    radian = angle*(M_PI / 180.0f);
}


inline float toRadianForBox2d(float angle){   
    return M_PI/2 - angle*(M_PI / 180.0f);
}

inline float toAngle(float radian){
    return radian * 180.0f / M_PI;
}

inline void toAngle(float radian, float& angle){
    angle = radian/(M_PI / 180.0f);
}

inline float toAngleForGame(float radian){
    radian = M_PI/2 + radian;
    float angle = toAngle(radian);
    return angle;
}

inline Vector2D rotate90(const Vector2D& p, float cx, float cy) {
    float newX = cx - (p.y - cy);
    float newY = cy + (p.x - cx);
    return {newX, newY};
}


inline float box2dToPixelX(float x) { return x * PIXELS_PER_METER; }
inline float box2dToPixelY(float y) { return y * PIXELS_PER_METER;}
inline float pixelToBox2dX(float x) { return x / PIXELS_PER_METER; }
inline float pixelToBox2dY(float y) { return y / PIXELS_PER_METER;}

inline float box2dToPixelAngle(float box2dAngle) {
    return (M_PI / 2.0f - box2dAngle) * (180.0f / M_PI);
}
