#ifndef BOIDSIM
#define BOIDSIM
    #include "boidsim.hpp"
#endif

#ifndef MATH
#define MATH
    #include "math.hpp"
#endif

float dist(Vector2f v1, Vector2f v2) {
    Vector2f relVec = (v1 - v2);
    float mag = sqrt(relVec.x * relVec.x + relVec.y * relVec.y);

    return mag;
}


float magnitude(Vector2f v) {
    return dist(v, Vector2f(0.0f, 0.0f));
}


Vector2f normalize(Vector2f v, float unit) {
    float mag = magnitude(v);
    if (mag == 0.0f) {
        return Vector2f(0.0f, 0.0f);
    }

    v *= (unit/mag);

    return v;
}


float dot(Vector2f v1, Vector2f v2) {
    float dotProduct = v1.x * v2.x + v1.y * v2.y;

    return dotProduct;
}


float angle(Vector2f v1, Vector2f v2) {
    float magProd = magnitude(v1) * magnitude(v2);

    if(magProd == 0.0f) {
    	return magProd;
    }

    float angle = acos(dot(v1, v2)/magProd);
    // float angle = atan2(v1.x*v2.y-v1.y*v2.x, v1.x*v2.x+v1.y*v2.y);
    
    return angle;
}


float min(float a, float b) {
    return a*(a < b) + b*(b <= a);
}


float max(float a, float b) {
    return a*(a > b) + b*(b >= a);
}